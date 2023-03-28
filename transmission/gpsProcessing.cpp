#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"


// UART SETUP
#define UART_ID uart1
#define BAUD_RATE 9600

// Transmission/Send/Output 
#define UART_TX_PIN 4

// Reciever/Input 
#define UART_RX_PIN 5

#define PARITY    UART_PARITY_NONE

// USE THIS METHOD TO READ IN RAW GPS DATA

void package_GPGGA(std::string s, char delimiter, std::string& output)
{
    std::stringstream stream(s);
    std::string word;
    std::string binary_string = "";
    std::string output_string = "";
    int index = 0;

    while (!stream.eof()) {

        getline(stream, word, delimiter);
        //cout << word << endl;
        if (index == 0 && word != "$GPGGA")
            break;
        else if (index == 1 || index == 2 || index == 4 || index == 6 || index == 9) {
            binary_string += word;
            binary_string += ",";
        }
        index++;
    }

    if (binary_string != "") {
        // for (size_t i = 0; i < binary_string.size(); i++)
        //     // output_file << binary_string[i]; //this is for plaintxt
        //     output_string += std::bitset<8>(binary_string[i]).to_string();
        // // output_file << endl;
        // output = output_string;
        output = binary_string;
    }
}

// TRANSMISSION AX25 STRUCT
typedef struct ax25_frame_s {
    std::bitset<8> START_FLAG;
    std::bitset<56> DEST_ADDR;
    std::bitset<56> SRC_ADDR;
    std::bitset<448> DIGIPEATER_ADDR;
    std::bitset<8> CTRL_FIELD;
    std::bitset<8> PROTOCOL_ID;
    std::string INFO;
    std::bitset<16> FCS;
    std::bitset<8> END_FLAG;
} ax25_frame_send;

int main(int argc, char **argv){

    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // string file_name=argv[1];

    // ifstream inFile;
    // ofstream outFile;
    // string outFileName = "binary_gps_data.txt";
    // string outFileName = "parsed_gps_data.txt";
    // inFile = ifstream(file_name, ios_base::in);
 
        //READ LINE BY LINE, send GPGGA data to outfile in binary;
        // outFile.open(outFileName);
    while(true) {

        std::string raw_data_line = "";
        std::string parsed_data_line = "";
        std::string binary_string = "";

        // Read/Parse raw data, write to line var
        
        //SAVE GPGGA
        char c = uart_getc(UART_ID);
        while (c != '\n') {
            raw_data_line += c;
            c = uart_getc(UART_ID);
        }
        
        package_GPGGA(raw_data_line, ',', parsed_data_line);

        std::cout << "Raw Data from GPS: ";
        std::cout << raw_data_line << std::endl;
        raw_data_line = "";
    
    
        // packaging the parsed data
        ax25_frame_send ax25_frame;

        ax25_frame.START_FLAG = 126;
        binary_string += ax25_frame.START_FLAG.to_string().c_str();

        ax25_frame.DEST_ADDR = 32167;
        binary_string += ax25_frame.DEST_ADDR.to_string();

        ax25_frame.SRC_ADDR = 655852;
        binary_string += ax25_frame.SRC_ADDR.to_string();

        ax25_frame.DIGIPEATER_ADDR = 487392983;
        binary_string += ax25_frame.DIGIPEATER_ADDR.to_string();

        ax25_frame.CTRL_FIELD = 255;
        binary_string += ax25_frame.CTRL_FIELD.to_string();

        ax25_frame.PROTOCOL_ID = 254;
        binary_string += ax25_frame.PROTOCOL_ID.to_string();

        ax25_frame.INFO = parsed_data_line;
        binary_string += ax25_frame.INFO;

        ax25_frame.FCS = 1024;
        binary_string += ax25_frame.FCS.to_string();

        ax25_frame.END_FLAG = 126;
        binary_string += ax25_frame.END_FLAG.to_string();

        // std::cout << ax25_frame.START_FLAG << ax25_frame.DEST_ADDR << ax25_frame.SRC_ADDR << ax25_frame.DIGIPEATER_ADDR << ax25_frame.CTRL_FIELD << ax25_frame.PROTOCOL_ID << ax25_frame.INFO << ax25_frame.FCS << ax25_frame.END_FLAG << std::endl;

        // uart_puts( t, binary_string.c_str()); will likely use a dedicated to_rf function instead
        // printf(binary_string.c_str());
        std::cout << "###################" << std::endl;
        std::cout << "GPGGA DATA ONLY: ";
        std::cout << parsed_data_line.c_str() << std::endl;

        }
        

    while(1)
        tight_loop_contents();
    
}

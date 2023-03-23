#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>

// UART SETUP
#define UART_ID uart0
#define BAUD_RATE 9600

// # Transmission/Send/Output #
#define UART_TX_PIN 4

// # Reciever/receiver #
#define UART_RX_PIN  5

// RECEIVING AX25 FRAME
typedef struct ax25_frame_r {
    int START_FLAG;
    int DEST_ADDR;
    int SRC_ADDR;
    int DIGIPEATER_ADDR;
    int CTRL_FIELD;
    int PROTOCOL_ID;
    std::string INFO;
    int FCS;
    int END_FLAG;
} ax25_frame_receiver;

std::string unparse_bin(std::string binary_line) {
    std::string line = binary_line;
    std::stringstream sstream(line);
    std::string unparsed_line;



    while(sstream.good()) {
        std::bitset<8> current_character;
        sstream >> current_character;
        char c = char(current_character.to_ulong());
        //std::cout << c;
        unparsed_line += c;
    }
    // std::cout << unparsed_line;
    return unparsed_line.substr(0,unparsed_line.length()-1);
}


int main() {
    
    // Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    ax25_frame_r receiver_ax25_frame;

    // LOOP TO READ FROM 
    while(true) {

        std::string raw_data_line = "";
        std::string START_FLAG;
        std::string DEST_ADDR;
        std::string SRC_ADDR;
        std::string DIGIPEATER_ADDR;
        std::string CTRL_FIELD;
        std::string PROTOCOL_ID;
        std::string INFO;
        std::string FCS;
        std::string END_FLAG;


        if(uart_is_readable(UART_ID)){
            while(uart_is_readable(UART_ID)){
                //SAVE GPGGA
                char c = uart_getc(UART_ID);
                raw_data_line += c;
            }
            receiver_ax25_frame.START_FLAG = std::stoi(START_FLAG, 0, 2);
            receiver_ax25_frame.START_FLAG = std::stoi(DEST_ADDR, 0, 2);
            receiver_ax25_frame.SRC_ADDR = std::stoi(SRC_ADDR, 0, 2);
            receiver_ax25_frame.SRC_ADDR = std::stoi(DIGIPEATER_ADDR, 0, 2);
            receiver_ax25_frame.CTRL_FIELD = std::stoi(CTRL_FIELD, 0, 2);
            receiver_ax25_frame.PROTOCOL_ID = std::stoi(PROTOCOL_ID, 0, 2);

            INFO = unparse_bin(raw_data_line);    
            receiver_ax25_frame.INFO = INFO;
            
            receiver_ax25_frame.FCS = std::stoi(FCS, 0, 2);
            receiver_ax25_frame.END_FLAG = std::stoi(END_FLAG, 0, 2);
        }

        uart_puts(UART_ID, INFO.c_str());
    }

    while (1)
        tight_loop_contents();
}
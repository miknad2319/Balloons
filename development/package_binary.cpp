#include <fstream>
#include <string>
#include <iostream>
#include <bitset>
//#include "pico/stdlib.h"
//will need to include header files for ax25 / APRS protocols here
// READ FROM BINARY_GPS_DATA

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
} ax25_frame;

int main (int argc, char **argv) {

    std::string inputFileName = argv[1];
    std::string outputFileName = "ax25_frame_data_concat.txt";
    std::string line;
    std::string ax25_array[332]; // max possible bytes in ax.25 frame
    std::ifstream inFile = std::ifstream(inputFileName);
    std::ofstream outFile;

    int num_frames = 1;

    ax25_frame_s ax25_frame;

    outFile.open(outputFileName);
    while(!inFile.eof()) {//&& num_frames <= 1
        getline(inFile, line);
        // std::cout << line << std::endl;
        //dummy values for all parameters besides INFO (gps data)
        ax25_frame.START_FLAG = 126;
        ax25_frame.DEST_ADDR = 32167;
        ax25_frame.SRC_ADDR = 655852;
        ax25_frame.DIGIPEATER_ADDR = 487392983;
        ax25_frame.CTRL_FIELD = 255;
        ax25_frame.PROTOCOL_ID = 254;
        ax25_frame.INFO = line;
        ax25_frame.FCS = 1024;
        ax25_frame.END_FLAG = 126; 
        //num_frames++;
        outFile << ax25_frame.START_FLAG << ax25_frame.DEST_ADDR << ax25_frame.SRC_ADDR << ax25_frame.DIGIPEATER_ADDR << ax25_frame.CTRL_FIELD << ax25_frame.PROTOCOL_ID << ax25_frame.INFO << ax25_frame.FCS << ax25_frame.END_FLAG << std::endl;

    }

    // outFile << "Start Flag: " << ax25_frame.START_FLAG << std::endl;
    // outFile << "Destination Address: " << ax25_frame.DEST_ADDR << std::endl;
    // outFile << "Source Address: " << ax25_frame.SRC_ADDR << std::endl;
    // outFile << "Digipeater_Addresses: " << ax25_frame.DIGIPEATER_ADDR << std::endl;
    // outFile << "Control Field: " << ax25_frame.CTRL_FIELD << std::endl;
    // outFile << "Protocol ID: " << ax25_frame.PROTOCOL_ID << std::endl;
    // outFile << "Frame Info Field: " << ax25_frame.INFO << std::endl;
    // outFile << "FCS: " << ax25_frame.FCS << std::endl;
    // outFile << "End Flag: " << ax25_frame.END_FLAG << std::endl << std::endl;
    // outFile << "Concatenated: ";
    outFile << ax25_frame.START_FLAG << ax25_frame.DEST_ADDR << ax25_frame.SRC_ADDR << ax25_frame.DIGIPEATER_ADDR << ax25_frame.CTRL_FIELD << ax25_frame.PROTOCOL_ID << ax25_frame.INFO << ax25_frame.FCS << ax25_frame.END_FLAG << std::endl;
    

}   

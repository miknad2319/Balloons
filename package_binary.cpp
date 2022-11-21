#include <fstream>
#include <string>
#include <iostream>
#include <bitset>
//#include "pico/stdlib.h"
//will need to include header files for ax25 / APRS protocols here

typedef struct ax25_frame_s {
    std::bitset<8> START_FLAG;
    std::bitset<56> DEST_ADDR;
    std::bitset<56> SRC_ADDR;
    std::bitset<448> DIGIPEATER_ADDR;
    std::bitset<8> CTRL_FIELD;
    std::bitset<8> PROTCOL_ID;
    std::string INFO;
    std::bitset<16> FCS;
    std::bitset<8> END_FLAG;
} ax25_frame;

int main (int argc, char **argv) {

    std::string inputFileName = argv[1];
    std::string outputFileName = "ax25_frame_data";
    std::string line;
    std::string ax25_array[332]; // max possible bytes in ax.25 frame
    std::ifstream inFile = std::ifstream(inputFileName);
    std::ofstream outFile;

    int num_frames = 1;

    ax25_frame_s ax25_frame;
    while(!inFile.eof() && num_frames <= 5) {
        getline(inFile, line);
        // std::cout << line << std::endl;
        //dummy values for all parameters besides INFO (gps data)
        ax25_frame.START_FLAG = 126;
        ax25_frame.DEST_ADDR = 32767;
        ax25_frame.SRC_ADDR = 65535;
        ax25_frame.DIGIPEATER_ADDR = 487392983;
        ax25_frame.CTRL_FIELD = 255;
        ax25_frame.PROTCOL_ID = 254;
        ax25_frame.INFO = line;
        ax25_frame.FCS = 1024;
        ax25_frame.END_FLAG = 126; 
        num_frames++;
    }
    std::cout << "Start Flag: " << ax25_frame.START_FLAG << std::endl;
    std::cout << "Destination Address: " << ax25_frame.DEST_ADDR << std::endl;
    std::cout << "Source Address: " << ax25_frame.INFO << std::endl;
    std::cout << "Digipeater_Addresses: " << ax25_frame.DIGIPEATER_ADDR << std::endl;
    std::cout << "Control Field: " << ax25_frame.CTRL_FIELD << std::endl;
    std::cout << "Protocol ID: " << ax25_frame.PROTCOL_ID << std::endl;
    std::cout << "Frame Info Field: " << ax25_frame.INFO << std::endl;
    std::cout << "FCS: " << ax25_frame.FCS << std::endl;
    std::cout << "End Flag: " << ax25_frame.END_FLAG << std::endl;
}   
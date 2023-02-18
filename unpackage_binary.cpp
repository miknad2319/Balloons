#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <bitset>

// READ FRIM AX25_FRAME_DATA_CONCAT

typedef struct ax25_frame_s {
    int START_FLAG;
    int DEST_ADDR;
    int SRC_ADDR;
    int DIGIPEATER_ADDR;
    int CTRL_FIELD;
    int PROTOCOL_ID;
    std::string INFO;
    int FCS;
    int END_FLAG;
} ax25_frame;

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


int main (int argc, char **argv) {
    std::string inputFileName = argv[1];
    std::string outputFileName = "unparsed_ax25_frame.txt";
    std::string decoded_gps_file = "decoded_gps_data.txt";
    std::string line;
    std::ifstream inFile = std::ifstream(inputFileName);
    std::ofstream outFile;
    std::ofstream gpsFile;
    ax25_frame_s input_ax25_frame;

    outFile.open(outputFileName);

    //DEBUGGING CODE, LIKELY WON'T USE IN FINAL PRODUCT
   // #################################################
    while(!inFile.eof()) {
        getline(inFile, line);
        if (line.length() > 1) {

        std::string START_FLAG = line.substr(0,8);
        outFile << "Start Flag as STR: " << START_FLAG << std::endl; 
        outFile << "Start Flag as INT: " << std::stoi(START_FLAG, 0, 2) << std::endl;
        input_ax25_frame.START_FLAG = std::stoi(START_FLAG, 0, 2);

        std::string DEST_ADDR = line.substr(8,56);
        outFile << "Destination Address as STR: " << DEST_ADDR << std::endl; 
        outFile << "Destination Address as INT: " << std::stoi(DEST_ADDR, 0, 2) << std::endl;
        input_ax25_frame.START_FLAG = std::stoi(DEST_ADDR, 0, 2);
       
        std::string SRC_ADDR = line.substr(64,56);
        outFile << "Source Address as STR: " << SRC_ADDR << std::endl; 
        outFile << "Source Address as INT: " << std::stoi(SRC_ADDR, 0, 2) << std::endl;
        input_ax25_frame.SRC_ADDR = std::stoi(SRC_ADDR, 0, 2);

        std::string DIGIPEATER_ADDR = line.substr(120, 448);
        outFile << "DIGIPEATER_ADDR as STR: " << DIGIPEATER_ADDR << std::endl; 
        outFile << "DIGIPEATER_ADDR as INT: " << std::stoi(DIGIPEATER_ADDR, 0, 2) << std::endl;
        input_ax25_frame.SRC_ADDR = std::stoi(DIGIPEATER_ADDR, 0, 2);

        std::string CTRL_FIELD = line.substr(568,8);
        outFile << "CTRL_FIELD as STR: " << CTRL_FIELD << std::endl; 
        outFile << "CTRL_FIELD as INT: " << std::stoi(CTRL_FIELD, 0, 2) << std::endl;
        input_ax25_frame.CTRL_FIELD = std::stoi(CTRL_FIELD, 0, 2);

        std::string PROTOCOL_ID = line.substr(576,8);
        outFile << "PROTOCOL_ID as STR: " << PROTOCOL_ID << std::endl; 
        outFile << "PROTOCOL_ID as INT: " << std::stoi(PROTOCOL_ID, 0, 2) << std::endl;
        input_ax25_frame.PROTOCOL_ID = std::stoi(PROTOCOL_ID, 0, 2);

        std::string INFO = line.substr(584,line.size()-24-584);
        outFile << "INFO as BIN STR: " << INFO << std::endl;
       // std::cout << "INFO as BIN STR: " << INFO << std::endl;
        std::string unparsed_line = unparse_bin(INFO);
        outFile << "INFO as csv: " << unparsed_line << std::endl;
        //std::cout << "INFO as csv: " << unparsed_line << std::endl;
        input_ax25_frame.INFO = unparsed_line;

        std::string FCS = line.substr(line.size()-24, 16);
        outFile << "FCS as STR: " << FCS << std::endl; 
        outFile << "FCS as INT: " << std::stoi(FCS, 0, 2) << std::endl;
        input_ax25_frame.FCS = std::stoi(FCS, 0, 2);

        std::string END_FLAG = line.substr(line.size()-8, 8);
        outFile << "END_FLAG as STR: " << END_FLAG << std::endl; 
        outFile << "END_FLAG as INT: " << std::stoi(END_FLAG, 0, 2) << std::endl;
        input_ax25_frame.END_FLAG = std::stoi(END_FLAG, 0, 2);

        //outFile << input_ax25_frame.START_FLAG << input_ax25_frame.DEST_ADDR << input_ax25_frame.SRC_ADDR << input_ax25_frame.DIGIPEATER_ADDR << input_ax25_frame.CTRL_FIELD << input_ax25_frame.PROTOCOL_ID << input_ax25_frame.INFO << input_ax25_frame.FCS << input_ax25_frame.END_FLAG;

        outFile << std::endl << "AX25 FRAME" << std::endl;
        }
    }

    outFile.close();
    // #################################################

    // inFile.seekg(0); // move to beginning
    // inFile.clear(); // clear EOF flag 

   // DECODED_GPS_TXT
    inFile = std::ifstream(inputFileName);
    gpsFile.open(decoded_gps_file);

    while(!inFile.eof()) {
        getline(inFile, line);
        if (line.length() > 1) {
            std::string INFO = line.substr(584,line.size()-24-584);
            // std::cout << INFO << std::endl;
            std::string unparsed_line = unparse_bin(INFO);
            // std::cout << unparsed_line << std::endl;
            gpsFile << unparsed_line << std::endl;
        }
    }
    
    return 0;
}


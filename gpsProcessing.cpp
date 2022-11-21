#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
// #include <Radiolib.h>
//#include "pico/stdlib.h"
using namespace std;

void package_GPGGA(string s, char delimiter, ostream& output_file)
{
    stringstream stream(s);
    string word;
    string binary_string = "";
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
        for (size_t i = 0; i < binary_string.size(); i++)
            output_file << bitset<8>(binary_string[i]);
        output_file << endl;
    }
}

int main(int argc, char **argv){
    string file_name=argv[1];
    string line;
    ifstream inFile;
    ofstream outFile;
    string outFileName = "binary_gps_data.txt";
    inFile = ifstream(file_name, ios_base::in);
    if(!inFile.is_open() ){
        cout<<"CANNOT OPEN"<<endl;
        exit(1);
    }
    else{
        //READ LINE BY LINE, send GPGGA data to outfile in binary;
        outFile.open(outFileName);
        while(!inFile.eof()){
            //SAVE GPGGA
            getline(inFile, line);
            package_GPGGA(line, ',', outFile);
        }
    }
}

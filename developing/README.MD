# Balloons

This is a full pipeline minus the pico integration.

Raw GPS data is fed into gpsProcessing, which will output parsed versions of GPGGA data (discards data with other headers) in a binary string into binary_gps_data.  
We will then use package_binary to assemble the AX25 frame for each line of binary_gps_data. In this example I made up values for the header values, but when it comes to actual implementation we should have actual values provided to us. Also pretty sure we don't need digipeater addresses.  
In unpackage_binary we read in each binary AX25 frame and decode each. In this instance we are decoding / parsing the binary frame for the GPS data. We send the plaintext gps data to decoded_gps_data and the frame data to ax25_frame_data, with examples of binary and plaintext (in case we need one or the other)


** Not compiled with "pico/stdlib.h"** Compile with regular ol' g++ **
 ---  
### The Pipeline

rawGPS.txt -> ** gpsProcessing.cpp ** -> (binary_gps_data.txt, parsed_gps_data.txt)  
binary_gps_data.txt -> ** package_binary.cpp ** -> ax25_frame_data_concat.txt  
ax25_frame_data_concat.txt -> ** unpackage_binary.cpp ** -> (unparsed_ax25_frame.txt, decoded_gps_data.txt)

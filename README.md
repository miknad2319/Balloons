# Balloons
Right now not much going on. Parsing raw gps data into binary, creating dummy ax25 frame fields.
**Not compiled with "pico/stdlib.h"** Compile with regular ol' g++
Flow so far is rawGPS -> gpsProcessing -> binary_gps_data -> package_binary -> ax25_frame_data

#!/usr/bin/python3
import serial
import time

ser = serial.Serial('/dev/tty.usbmodem21301', 115200)
print(ser.name)
i = 0
while True:
    line = ser.readline().decode('utf-8')
    cleaned_line = line[:-4]
    if i % 10 == 0 and i != 0:  
        print(f"{i}: Data appended")
        ui_data_file = open("ui_data_2.txt", "a")
        ui_data_file.write(f"{cleaned_line}\n")
        ui_data_file.close()
        i = 0
    else:
        print(i)
        i += 1
    print("UTC TIME  |   LAT   |   LONG   |SATS|ELEVATION")
    print(cleaned_line)
    

    










# class ReadLine:
#     def __init__(self, s):
#         self.buf = bytearray()
#         self.s = s
    
#     def readline(self):
#         i = self.buf.find(b"\n")
#         if i >= 0:
#             r = self.buf[:i+1]
#             self.buf = self.buf[i+1:]
#             return r
#         while True:
#             i = max(1, min(2048, self.s.in_waiting))
#             data = self.s.read(i)
#             i = data.find(b"\n")
#             if i >= 0:
#                 r = self.buf + data[:i+1]
#                 self.buf[0:] = data[i+1:]
#                 return r
#             else:
#                 self.buf.extend(data)

# ser = serial.Serial('/dev/tty.usbmodem21301', 115200)
# while True:
#     rl = ReadLine(ser)
#     print(rl)
from collections import deque
import time

def tail(filename, n=1):
    return deque(open(filename), n)
while True:
    data = tail("ui_data_2.txt")[0]
    print(data)
    time.sleep(10)
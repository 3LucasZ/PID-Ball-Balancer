from serial import Serial
import numpy as np
import matplotlib.pyplot as plt

ser = Serial('/dev/cu.usbmodem21101',9600,timeout=1)
print("Reading from:",ser.name)


start = 0
current = 0

while True:
    ret = ser.readline().decode("utf-8").strip("\r\n")
    print(ret)
    ret = ret.split(",")
    for entry in ret:
        entry = entry.split(":")
        if (entry[0]=='Error'):
            plt.plot(current,entry[1])
            print(entry[1])

    plt.axis([start,start+50*40,-20,20])
    current+=40
    if (current >= start+50*40):
        start+=40
        
    plt.show()

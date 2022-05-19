from serial import Serial
import numpy as np
import matplotlib.pyplot as plt

ser = Serial('/dev/cu.usbmodem21101',9600)
print("Reading from:",ser.name)

CYCLES = 40
CYCLE_TIME = 50

x=[0]
y=[0]
#plt.style.use('_mpl-gallery')
fig, ax =plt.subplots()
plt.ion()
ax.set(xlim=(0, CYCLES*CYCLE_TIME), xticks=np.arange(0, CYCLES*(CYCLE_TIME+1), CYCLE_TIME*5))
ax.set(yticks=np.arange(-20, 22, 4))
ax.set_ylim(ymin=-20,ymax=20)
ax.spines['bottom'].set_position('zero')
curX = 0
curY = 0

while True:
    ret = ser.readline().decode("utf-8").strip("\r\n")
    print(ret)
    ret = ret.split(",")
    for entry in ret:
        entry = entry.split(":")
        if (entry[0]=='Error'):
            curX = x[-1]+CYCLE_TIME
            curY = float(entry[1])
            print(entry[1])
    x.append(curX)
    y.append(curY)
    if (len(x)>CYCLES):
        del x[0]
        del y[0]

    ax.set(xlim=(x[0], x[0]+CYCLES*CYCLE_TIME), xticks=np.arange(x[0], x[0]+CYCLES*(CYCLE_TIME+1), CYCLE_TIME*5))
    ax.plot(x,y,linewidth=2.5,color="blue")
    ax.fill(x,y,'b',alpha=0.3)

    plt.show()
    plt.pause(0.001)

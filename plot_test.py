import numpy as np
import matplotlib.pyplot as plt

x=np.arange(0,50)
y=np.sin(x)

fig, ax =plt.subplots()

ax.plot(x,y,linewidth=2.5,color="blue")
ax.fill_between(x,y,alpha=0.3)
ax.set_title('PID error graph')
ax.set_xlabel('time (sec)')
ax.set_ylabel('error (cm)')
plt.show()

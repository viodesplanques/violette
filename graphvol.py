import numpy as np
import matplotlib.pyplot as plt

evolvol=[]
with open("volume.txt", 'r') as f:
    for i in range(0, 365):
        volume=f.readline()
        evolvol.append(float(volume))
    
x=np.arange(0,365,1)
plt.plot(x, evolvol)
plt.fill_between(x, evolvol, facecolor='lightblue', alpha=2.5)
plt.xlabel('Temps [j]')
plt.ylabel('Superficie [km^2]')
plt.title('Evolution du continent plastique au cours du temps')
plt.xlim(x[0],x[-1])
plt.ylim(evolvol[0],20000000)
plt.axhline(y=551695, color='purple',label='France')
plt.axhline(y=9147590, color='red',label='Etats-Unis')
plt.axhline(y=17125191, color='orange',label='Russie')
plt.legend(loc='upper left')
plt.show()
#plt.savefig('Degradation3%.png')
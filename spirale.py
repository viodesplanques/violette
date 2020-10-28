import numpy as np
import matplotlib.pyplot as plt

p= 2
angle=0
x=[]
y=[]
for i in range(0, 1000):
    a=p*np.cos(angle)
    b=p*np.sin(angle)
    x.append(a)
    y.append(b)
    p+=2
    angle+=np.pi/100
plt.plot(x,y)
plt.show()
 
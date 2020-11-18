import numpy as np
import matplotlib.pyplot as plt
import math
xplas= 3205.64
yplas= 2732
xpart=4808.46
ypart=1061
diffx= xpart-xplas
diffy= ypart-yplas
p= math.sqrt(diffx**2+diffy**2)
if diffx>=0 and diffy>=0:
    angle=math.acos(abs(diffx)/p)
elif diffx<0 and diffy>=0:
    angle=np.pi/2 + math.acos(abs(diffx)/p)
elif diffx<0 and diffy<0:
    angle= np.pi +math.acos(abs(diffx)/p)
elif diffx>=0 and diffy<0:
    angle=3*np.pi/2+math.acos(abs(diffx)/p)
x=[xpart]
y=[ypart]
while p>200:
    p-= p/20
    angle -= np.pi/10
    xpart = xplas+p*np.cos(angle)
    ypart = yplas+p*np.sin(angle)
    x.append(xpart)
    y.append(ypart)
plt.plot(x,y)
plt.show()
 
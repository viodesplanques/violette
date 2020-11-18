# -*- coding: utf-8 -*-
"""
Created on Wed Nov 11 13:44:10 2020

@author: Marguerite Larriere
"""

from matplotlib import pyplot as plt
import numpy as np 
import math

fig, ax = plt.subplots(figsize=(18,12))


t = np.array([0,10])

Oya_shivo = plt.subplot2grid((6, 6), (0, 0), colspan=2) 
Oya_shivo.plot((0.02)*t, -(0.02)*t, label='Oya_shivo')
Oya_shivo.xaxis.set_visible(False)
Oya_shivo.yaxis.set_visible(False)
Oya_shivo.legend()

Alaska = plt.subplot2grid((6, 6), (0, 2), colspan=2) 
Alaska.plot(-1.56*t, -1.56*t, label='Alaska')
Alaska.xaxis.set_visible(False)
Alaska.yaxis.set_visible(False)
Alaska.legend()

Kurishivo= plt.subplot2grid((6, 6), (1, 0), rowspan=2) 
Kurishivo.plot(5*t, 0.72*t, label='Kurishivo')
Kurishivo.xaxis.set_visible(False)
Kurishivo.yaxis.set_visible(False)
Tokyo= Kurishivo.scatter(0,0.5, color='orange',label='Tokyo') #(0; 1629.90 km)
Kurishivo.legend()

Nord_equatorial2= plt.subplot2grid((6, 6), (3, 0), colspan=2)
Nord_equatorial2.plot(-4.17*t, 0.9*t, label='Nord_equatorial2')
Nord_equatorial2.xaxis.set_visible(False)
Nord_equatorial2.yaxis.set_visible(False)
Nord_equatorial2.legend()

Nord_equatorial1= plt.subplot2grid((6, 6), (3, 2), colspan=2)
Nord_equatorial1.plot(-4.17*t, 0*t, label='Nord_equatorial1')
Nord_equatorial1.xaxis.set_visible(False)
Nord_equatorial1.yaxis.set_visible(False)
Nord_equatorial1.legend()

California= plt.subplot2grid((6, 6), (1, 3), rowspan=2)
California.plot(-0.072*t, -0.9*t, label='California')
California.xaxis.set_visible(False)
California.yaxis.set_visible(False)
Vancouver= California.scatter(0,0, color='black', label='Vancouver') #(6411.29 km;2906.53 km)
San_Fransisco= California.scatter(0,-2, color='red', label='San Fransisco') #(6411.29 km;2307 km
LA= California.scatter(0,-6, color='green', label='Los Angeles')#(6411.29 km;1061.80 km)
California.legend()


Spirale = plt.subplot2grid((6, 6), (1, 1), rowspan=2, colspan=2) 
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
plt.plot(x,y, label='Spirale')
Spirale.legend()
Spirale.xaxis.set_visible(False)
Spirale.yaxis.set_visible(False)

plt.tight_layout(pad=0)

plt.show()
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 11 13:44:10 2020

@author: Marguerite Larriere
"""

from matplotlib import pyplot as plt
import numpy as np 
import matplotlib.cbook as cbook
import matplotlib.colors as colors
import random as rand

fig, ax = plt.subplots(figsize=(18,12))

t = np.array([0,10])

Oya_shivo = plt.subplot2grid((6, 6), (0, 0), colspan=2) 
Oya_shivo.plot((0.02)*t, -(0.02)*t)
Oya_shivo.set_title('Oya_shivo')
Oya_shivo.xaxis.set_visible(False)
Oya_shivo.yaxis.set_visible(False)

Alaska = plt.subplot2grid((6, 6), (0, 2), colspan=2) 
Alaska.plot(-1.56*t, -1.56*t)
Alaska.set_title('Alaska')
Alaska.xaxis.set_visible(False)
Alaska.yaxis.set_visible(False)

Kurishivo= plt.subplot2grid((6, 6), (1, 0), rowspan=2) 
Kurishivo.plot(5*t, 0.72*t)
Kurishivo.set_title('Kurishivo')
Kurishivo.xaxis.set_visible(False)
Kurishivo.yaxis.set_visible(False)
#Tokyo= Kurishivo.scatter(0,1624.90)

Nord_equatorial2= plt.subplot2grid((6, 6), (3, 0), colspan=2)
Nord_equatorial2.plot(-4.17*t, 0.9*t)
Nord_equatorial2.set_title('Nord_equatorial2')
Nord_equatorial2.xaxis.set_visible(False)
Nord_equatorial2.yaxis.set_visible(False)

Nord_equatorial1= plt.subplot2grid((6, 6), (3, 2), colspan=2)
Nord_equatorial1.plot(-4.17*t, 0*t)
Nord_equatorial1.set_title('Nord_equatorial1')
Nord_equatorial1.xaxis.set_visible(False)
Nord_equatorial1.yaxis.set_visible(False)

California= plt.subplot2grid((6, 6), (1, 3), rowspan=2)
California.plot(-0.072*t, -0.9*t)
California.set_title('California')
California.xaxis.set_visible(False)
California.yaxis.set_visible(False)
#Vancouver= California.scatter(6411.29,2906.53)
#San_Fransisco= California.scatter(6411.29,2307)
#LA= California.scatter(6411.29,1061.80)

Spirale = plt.subplot2grid((6, 6), (1, 1), rowspan=2, colspan=2) 
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
Spirale.plot(x,y)

Spirale.set_title('Spirale')
Spirale.xaxis.set_visible(False)
Spirale.yaxis.set_visible(False)

plt.tight_layout()

plt.show()
from matplotlib import pyplot as plt
import numpy as np 
import math

fig, ax = plt.subplots(figsize=(18,12), sharex=True, sharey= True)


x=np.linspace(-0.5, 0.5, 10)

x=[np.concatenate((x,x,x,x,x), 0)]
x=np.reshape(x,(1,-1))
a=np.linspace(-0.06, 0.06,5)
y=[]
for i in range(0,len(a)):
    b=[a[i],a[i],a[i],a[i],a[i],a[i],a[i],a[i],a[i],a[i]]
    y.append(b)
    
Oya_shivo = plt.subplot2grid((6, 6), (0, 0), colspan=2) 
Oya_shivo.quiver(x, y,(0.02), -(0.02), label='Oya_shivo')
Oya_shivo.xaxis.set_visible(False)
Oya_shivo.yaxis.set_visible(False)
Oya_shivo.legend()

Alaska = plt.subplot2grid((6, 6), (0, 2), colspan=2) 
Alaska.quiver(x, y,-(1.56), -(1.56), label='Alaska')
Vancouver= Alaska.scatter(0.5,-0.05, color='red', label='Vancouver') #(6411.29 km;2906.53 km)
Alaska.xaxis.set_visible(False)
Alaska.yaxis.set_visible(False)
Alaska.legend(loc='upper left')

Kurishivo= plt.subplot2grid((6, 6), (1, 0), rowspan=2) 
Tokyo= Kurishivo.scatter(-0.5, 0.05, color='purple',label='Tokyo') #(0; 1629.90 km)
Kurishivo.quiver(x, y,(1), (0.92), width=0.02, label='Kurishivo')
Kurishivo.xaxis.set_visible(False)
Kurishivo.yaxis.set_visible(False)
Kurishivo.legend()

Nord_equatorial2= plt.subplot2grid((6, 6), (3, 0), colspan=2)
Nord_equatorial2.quiver(x, y,-(4.17), (0.9), label='Nord_equatorial2')
Nord_equatorial2.xaxis.set_visible(False)
Nord_equatorial2.yaxis.set_visible(False)
Nord_equatorial2.legend()

Nord_equatorial1= plt.subplot2grid((6, 6), (3, 2), colspan=2)
Nord_equatorial1.quiver(x, y,-(4.17), (0.1), label='Nord_equatorial1')
Nord_equatorial1.xaxis.set_visible(False)
Nord_equatorial1.yaxis.set_visible(False)
Nord_equatorial1.legend()

California= plt.subplot2grid((6, 6), (1, 3), rowspan=2)
California.quiver(x, y,-(0.072), -(0.9), width=0.02, label='California')
California.xaxis.set_visible(False)
California.yaxis.set_visible(False)
San_Fransisco= California.scatter(0.5,0.04, color='yellow', label='San Fransisco') #(6411.29 km;2307 km
LA= California.scatter(0.5,0, color='green', label='Los Angeles')#(6411.29 km;1061.80 km)
California.legend(loc='upper left')


Spirale = plt.subplot2grid((6, 6), (1, 1), rowspan=2, colspan=2) 
xplas=3205.64
yplas=2732
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

plt.plot(x,y, 'k-', label='Spirale')
plt.plot(x,y, 'k<')
Spirale.legend()
Spirale.xaxis.set_visible(False)
Spirale.yaxis.set_visible(False)

plt.tight_layout(pad=0)

plt.show()
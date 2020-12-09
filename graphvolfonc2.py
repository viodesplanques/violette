import numpy as np
import matplotlib.pyplot as plt

'''on stocke la taille du contient plastique en fonction du taux de degradation dans un tableau appelé evolvol'''
evolvol=[]
with open("volfonc2.txt", 'r') as f:
    for i in range(0, 40):
        volume=f.readline()
        evolvol.append(float(volume))
    
print(evolvol)
x=np.arange(0,5,0.25/2)
plt.plot(x, evolvol)
plt.fill_between(x, evolvol, facecolor='lightblue', alpha=2.5)
plt.xlabel('Degradation [%]')
plt.ylabel('Superficie continent plastique [km2]')
plt.title('Degradation des déchets dans le continent plastique')
plt.xlim(0,x[-1])
plt.ylim(0)
plt.axhline(y=551695, color='purple',label='France') 
plt.axhline(y=9147590, color='red',label='Etats-Unis') 
plt.axhline(y=17125191, color='orange',label='Russie') 
plt.legend(loc='upper left')
plt.savefig('Dégradation et Superficie.png')
plt.show()

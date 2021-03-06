import numpy as np
import matplotlib.pyplot as plt

'''on stocke la taille du continent plastique taille du contient plastique 
en fonction des tonnes de dechet deversées dans un tableau appelé evolvol'''
evolvol=[]
with open("volfonc.txt", 'r') as f:
    for i in range(0, 50):
        volume=f.readline()
        evolvol.append(float(volume))
    
print(evolvol)
x=np.arange(0,50*4,4)
plt.plot(x, evolvol)
plt.fill_between(x, evolvol, facecolor='lightblue', alpha=2.5)
plt.xlabel('Dechets deversés par les 4 villes [tonne/jour]')
plt.ylabel('Superficie continent plastique [km2]')  
plt.title('Accumulation des déchets dans le continent plastique en 1 an \n en fonction des quantités de déchets deversées par les villes')
plt.xlim(x[0],x[-1])
plt.ylim(0,20000000)

#Pour les volumes des pays, on a considéré une hauteur de 1m
plt.axhline(y=551695, color='purple',label='France')  #en km2
plt.axhline(y=9147590, color='red',label='Etats-Unis')  
plt.axhline(y=17125191, color='orange',label='Russie') 

plt.legend(loc='upper left')
plt.savefig('Accumulation des déchets en 1 an.png')
plt.show()
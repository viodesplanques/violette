#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// definition courant (on peut pas faire spirale parce que par le vx, vy)
struct Courants {
	double xAD;
	double yAB;
	double xBC;
	double yCD;
	double vitessex;
	double vitessey;
};

struct Courants courant[6];
	
// definition ville
struct Villes{
	char * nom;
	double xville;
	double yville;
	double dechet;
};
struct Villes ville[4];

// random int
int randomnb(int min , int max){
	double randomDomaine = RAND_MAX + 1.0;
    int entier1 = (int) (random() / randomDomaine * (abs(max)+abs(min)) +min);
    return entier1;
}

// random double
double random_double(double min , double max){
	double randomDomaine = RAND_MAX + 1.0;
    double entier1 = (double) (rand() / randomDomaine * (fabs(max)+fabs(min)) +min);
    return entier1;
}

// definition cadre total
double xmax= 6411.29;
double ymax= 3046.29;

//coordonnées plastiques( definir avec cadre
double xplas= 3205.64;
double yplas= 2732;

// spirale (quand la particule rentre dans la zonespi)
// probleme: car quand rentre peut en suite sortir donc il faut dire quand rentre sort plus JAMAIS
double spirale(double x, double y, int time, double historiq){
	double xplas= 3205.64;
	double yplas= 2732;
	double distspi=(x-xplas)*(x-xplas)+(y-yplas)*(y-yplas);
	double diffx= x-xplas;
	double diffy= y-yplas;
	double anglespi;
	if (diffx>=0 && diffy>=0) {
		anglespi=acos(fabs(diffx)/distspi);
	}
	else if (diffx<0 && diffy>=0) {
		anglespi=M_PI/2 + acos(fabs(diffx)/distspi);
	}
	else if (diffx<0 && diffy<0) {
		anglespi= M_PI +acos(fabs(diffx)/distspi);
	}
	else {
		anglespi=3*M_PI/2+acos(fabs(diffx)/distspi);
	}
	//printf("dist=%f", distspi);
	while (distspi>=200) {
		distspi-= distspi/20;
		anglespi -= M_PI/10;
		x= xplas + distspi*cos(anglespi);
		y= yplas+ distspi*sin(anglespi);
		time += 1;
		historiq[time][0]=x;
		historiq[time][1]=y;
		//printf("time=%d",time);
	}
	return historiq;
	//printf("%f,%f", x, y);
	// il faut aussi compter le temps et definir une fonction r qui diminue de - en - vite
}
		

//deplacement des particules + degradation
double deplacement(double x, double y, int time, double historiq){
	for (int i=0; i <6;i++){
		// identification de la zone courant
		if (x>=courant[i].xAD & x<=courant[i].xBC & y>=courant[i].yCD & y<=courant[i].yAB){
			x += courant[i].vitessex;
			y += courant[i].vitessey;
			x +=randomnb(-(courant[i].vitessex)/10,(courant[i].vitessex)/10);
			y +=randomnb(-(courant[i].vitessey)/10,(courant[i].vitessey)/10);
			time += 1;
			historiq[time][0]=x;
			historiq[time][1]=y;
			return deplacement(x, y, time, historiq);
			//printf("bouge avec %d time %d",i, time);
		}
		continue;
	}
	if (x<=0 & x>=xmax & y<=0 & y>=ymax){ //si est sorti du cadre > va vers ville la plus proche
		//printf("sortie\n");
		float dist =sqrt(pow((x-ville[0].xville),2)+pow((y-ville[0].yville),2));
		float a ;//variable pour stoker chaque dist
		for (int i=1; i<4; i++){
			a = sqrt(pow((x-ville[0].xville),2)+pow((y-ville[0].yville),2));
			if (a<= dist) {
				dist=a;
				int b=i; //variable pour stoker la ville la plus proche
				x = ville[b].xville;
				y = ville[b].yville;
				//printf("%s\n",ville[b].nom);
			}
		historiq[time][0]=x;
		historiq[time][1]=y;
		return deplacement(x, y, time+1,historiq);
		}
	}
	double xADspi=1602.82;
	double yABspi=2906.53;
	double xBCspi=4808.46;
	double yCDspi=1061.80;
	if (x>=xADspi & x<=xBCspi & y>=yCDspi & y<=yABspi){
		time=spirale(x, y, time, historiq); // il faut decider ce qu'on veut renvoyer + ajouter degradation 
		return time;
	}
	return 999;
}

int main(int argc, char * argv[]) {
    srand(time(NULL));
    
    // A. Courants
	// Alaska
	courant[0].xAD = 3205.64; // en km
	courant[0].yAB = 3046.57;
	courant[0].xBC = 6411.29;
	courant[0].yCD = 2906.53;
	courant[0].vitessex = -1.56*24; // km/j
	courant[0].vitessey = -1.56*24; // km/j

	//California
	courant[1].xAD = 4808.46;
	courant[1].yAB = 2906.53;
	courant[1].xBC = 6411.29;
	courant[1].yCD = 1061.80;
	courant[1].vitessex = -0.072*24 ; // km/j
	courant[1].vitessey = -0.9*24; // km/j

	//Kuroshivo
	courant[2].xAD = 0;
	courant[2].yAB = 2906.53;
	courant[2].xBC = 1602.82;
	courant[2].yCD = 1061.80;
	courant[2].vitessex = randomnb(11,2)*24; // km/j
	courant[2].vitessey = 0.72*24; // km/j

	//Nord-equatorial 1
	courant[3].xAD = 3205.64;
	courant[3].yAB = 1061.80;
	courant[3].xBC = 6411.29;
	courant[3].yCD = 0;
	courant[3].vitessex = -4.17*24; // km/j
	courant[3].vitessey = 0*24; 
	
	//Nord-equatorial 2
	courant[5].xAD = 0;
	courant[5].yAB = 1061.80;
	courant[5].xBC = 3205.64;
	courant[5].yCD = 0;
	courant[5].vitessex = -4.17*24; // km/j
	courant[5].vitessey = 0.9*24 ;


	//Oya-shivo
	courant[4].xAD = 0;
	courant[4].yAB = 3046.57;
	courant[4].xBC = 6411.29;
	courant[4].yCD = 2906.53;
	courant[4].vitessex = 0.0144*24; // km/j
	courant[4].vitessey = -0.0144*24; // km/j

	// B. Villes
	ville[0].nom= "Vancouver";
	ville[0].xville=6411.29;
	ville[0].yville=2906.53;
	ville[0].dechet=1044*24/1000; // kg/j

	ville[1].nom= "San Fransisco";
	ville[1].xville=6411.29;
	ville[1].yville=2307.53;
	ville[1].dechet=1044*24/1000;

	ville[2].nom= "Los Angeles";
	ville[2].xville=6411.29;
	ville[2].yville=1061.80;
	ville[2].dechet=1044*24/1000;

	ville[3].nom= "Tokyo";
	ville[3].xville=0;
	ville[3].yville=1624.90;
	ville[3].dechet=1044*24/1000; //tonne par jour
	
	double historiq[365][2];
	
	for (int i=0; i<4; i++){
		printf("%d\n",deplacement(ville[0].xville, ville[0].yville,0, historiq);
	}
	return 0;
}

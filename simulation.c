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

struct Courants courant[4];

// definition ville
struct Villes{
	char * nom;
	double xville;
	double yville;
	double dechet;
};
struct Villes ville[4];

// random
int randomnb(int max , int min){
	double randomDomaine = RAND_MAX + 1.0;
    int entier1 = (int) (rand() / randomDomaine * (abs(max)+abs(min)) +min);
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
void spirale(double x, double y, int time){
	double xADspi=1602.82;
	double yABspi=2906.53;
	double xBCspi=4808.46;
	double yCDspi=1061.80;
	double distspi=(x-xplas)*(x-xplas)+(y-yplas)*(y-yplas);
	double anglespi=acos((x-xplas)/distspi);
	while (x!=xplas) {
		distspi-= //fonc de diminution de r;
		anglespi -= M_PI/10;
		x= distspi*cos(anglespi);
		y= distspi*sin(anglespi);
		time += 1;
	}
	// il faut aussi compter le temps et definir une fonction r qui diminue de - en - vite
}

//deplacement des particules + degradation
void deplacement(double x, double y, int time){
	for (int i=0; i <5;i++){
		// identification de la zone courant
		if (x>=courant[i].xAD & x<=courant[i].xBC & y>=courant[i].yCD & y<=courant[i].yAB){
			x += courant[i].vitessex;
			y += courant[i].vitessey;
			x +=randomnb(-(courant[i].vitessex)/10,(courant[i].vitessex)/10);
			y +=randomnb(-(courant[i].vitessey)/10,(courant[i].vitessey)/10);
			time += 1;
			// ajouter degradation
		}
	}
	if ((x<=0) & (x>=xmax) & (y<=0) & (y>=ymax)){ //si est sorti du cadre > va vers ville la plus prochefloat
		float dist =sqrt(pow((x-ville[0].xville),2)+pow((y-ville[0].yville),2));
		float a ;//variable pour stoker chaque dist
		for (int i=1; i<4; i++){
			a = sqrt(pow((x-ville[0].xville),2)+pow((y-ville[0].yville),2));
			if (a<= dist) {
				dist=a;
				int b=i; //variable pour stoker la ville la plus proche
				x = ville[b].xville;
				y = ville[b].yville;
			}

		deplacement(x, y, time);
		}
	}
	double xADspi=1602.82;
	double yABspi=2906.53;
	double xBCspi=4808.46;
	double yCDspi=1061.80;
	if ((x>=xADspi) & (x<=xBCspi) & (y>=yCDspi) & (y<=yABspi)){
		spirale(x, y, time); // il faut decider ce qu'on veut renvoyer + ajouter degradation
	}
	else {
		deplacement(x, y, time);
	}
}

// random double
double random_double(double min , double max){
	double randomDomaine = RAND_MAX + 1.0;
    double entier1 = (double) (rand() / randomDomaine * (abs(max)+abs(min)) +min);
    return entier1;
}
// degradation que dans le continent de plastique
int degradation(double diminution, double r_ini){
	double tps_deg=0;
	while (r_ini>0) {
		double r_deg = r_ini - r_ini*diminution + random_double(0.001, 0.01) ;//rayon en fonction de la degradation du plastique par an
		r_ini -= r_deg; // le rayon diminue de r_deg
		if (r_ini<=0){
			r_ini+=0;
		}
		tps_deg += r_deg * 20; // 20 ans pour degrader un cercle de rayon 1cm
	}
	printf("temps =  %f \n",tps_deg);
}

int main(int argc, char * argv[]){
    srand(time(NULL));

    // A. Courants
	// Alaska
	courant[0].xAD = 3205.64; // en km
	courant[0].yAB = 3046.57;
	courant[0].xBC = 6411.29;
	courant[0].yCD = 2906.53;
	courant[0].vitessex = -1.56; // km/h
	courant[0].vitessey = -1.56; // km/h

	//California
	courant[1].xAD = 4808.46;
	courant[1].yAB = 2906.53;
	courant[1].xBC = 6411.29;
	courant[1].yCD = 1061.80;
	courant[1].vitessex = -0.072 ; // km/h
	courant[1].vitessey = -0.9; // km/h

	//Kuroshivo
	courant[2].xAD = 0;
	courant[2].yAB = 2906.53;
	courant[2].xBC = 1602.82;
	courant[2].yCD = 1061.80;
	courant[2].vitessex = randomnb(11,2); // km/h
	courant[2].vitessey = 0.72; // km/h

	//Nord-equatorial
	courant[3].xAD = 0;
	courant[3].yAB = 3046.57;
	courant[3].xBC = 3205.64;
	courant[3].yCD = 0;
	courant[3].vitessex = -4.17; // km/h
	courant[3].vitessey = 0;


	//Oya-shivo
	courant[3].xAD = 0;
	courant[3].yAB = 3046.57;
	courant[3].xBC = 6411.29;
	courant[3].yCD = 2906.53;
	courant[3].vitessex = 0.0144; // km/h
	courant[3].vitessey = -0.0144; // m par seconde à changer en km/h

	// B. Villes
	ville[0].nom= "Vancouver";
	ville[0].xville=6411.29;
	ville[0].yville=2906.53;
	ville[0].dechet=1044; // kg/h

	ville[1].nom= "San Fransisco";
	ville[1].xville=6411.29;
	ville[1].yville=2307.53;
	ville[1].dechet=1044;

	ville[2].nom= "Los Angeles";
	ville[2].xville=6411.29;
	ville[2].yville=1061.80;
	ville[2].dechet=1044;

	ville[3].nom= "Tokyo";
	ville[3].xville=0;
	ville[3].yville=1624.90;
	ville[3].dechet=1044;

	// degradation
	degradation(0.05, random_double(1.,9.)); //degradation d'une particule de 1cm est de environ 0.05cm/an et rayon initial compris entre 1 et 9 cm

}

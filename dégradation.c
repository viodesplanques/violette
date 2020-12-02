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

//degradation en fonction du volume du continent plastique (bis)
double degracont(int time, double * volcontinentplast){
	double volsphere=0;
	int nbsphere=0;
	double diminution=0.05*pow(10,-3)/365;
	double volfinal=0;
	while (volcontinentplast[time]>volsphere){
		double rayon=random_double(1,9)*pow(10,-3); //si on fait varier les rayon entre 1 et 9 cm il y a trop de sphere car en volume en km cube donc trop de calculs donc on fait des paquets de 1000 dechets
		volsphere+=4*M_PI*pow(rayon,3);
		nbsphere++;
		printf("rayon=%f __", rayon);
		double rayondegra=rayon*(1-diminution)-random_double(0.001, 0.01)*pow(10,-6);
		volfinal+=4*M_PI*pow(rayondegra,3)/3;
	}
	return volfinal;
}

//evolution de l'aire continent plastique
double evolutioncont(int time, int * tonneplastarrive, double * volcontinentplast){
	double mvplas=pow(10,-3);
	double volume=tonneplastarrive[time]/mvplas+volcontinentplast[time-1]*(1-random_double(0.000,0.0002));  //degracont(time-1, volcontinentplast);
	return volume;
	/*double aire=0;
	for (int i=0;i<tonneplastarrive[time]; i++){
		int r=randomnb(1,9);
		aire += 2*M_PI*r;
	}
	double airetot=volcontinentplast[time-1]/0.90+aire;
	return airetot;*/
}

// degradation que dans le continent de plastique
void degradation(double diminution, double r_ini){
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

// spirale (quand la particule rentre dans la zonespi)
// probleme: car quand rentre peut en suite sortir donc il faut dire quand rentre sort plus JAMAIS
int spirale(double x, double y, int time){
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
		distspi-= distspi/50;
		anglespi -= M_PI/10;
		x= xplas + distspi*cos(anglespi);
		y= yplas+ distspi*sin(anglespi);
		time += 1;
		//printf("time=%d",time);
	}
	return time;
	//printf("%f,%f", x, y);
	// il faut aussi compter le temps et definir une fonction r qui diminue de - en - vite
}
		
//defintion de r= rayon en fonction de la degradation du plastique

//deplacement des particules + degradation
int deplacement(double x, double y, int time){
	for (int i=0; i <6;i++){
		// identification de la zone courant
		if (x>=courant[i].xAD & x<=courant[i].xBC & y>=courant[i].yCD & y<=courant[i].yAB){
			x += courant[i].vitessex;
			y += courant[i].vitessey;
			x +=randomnb(-(courant[i].vitessex)/2,(courant[i].vitessex)/2);
			y +=randomnb(-(courant[i].vitessey)/2,(courant[i].vitessey)/2);
			time += 1;
			return deplacement(x, y, time);
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
		return deplacement(x, y, time+1);
		}
	}
	double xADspi=1602.82;
	double yABspi=2906.53;
	double xBCspi=4808.46;
	double yCDspi=1061.80;
	if (x>=xADspi & x<=xBCspi & y>=yCDspi & y<=yABspi){
		time=spirale(x, y, time); // il faut decider ce qu'on veut renvoyer + ajouter degradation 
		return time;
	}
	return 999;
}

int main(int argc, char * argv[]){
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
	courant[1].vitessex = -0.092*24 ; // km/j
	courant[1].vitessey = -0.9*24; // km/j

	//Kuroshivo
	courant[2].xAD = 0;
	courant[2].yAB = 2906.53;
	courant[2].xBC = 1602.82;
	courant[2].yCD = 1061.80;
	courant[2].vitessex = randomnb(11,2)*24; // km/j
	courant[2].vitessey = 0.9*24; // km/j

	//Nord-equatorial 1
	courant[3].xAD = 3205.64;
	courant[3].yAB = 1061.80;
	courant[3].xBC = 6411.29;
	courant[3].yCD = 0;
	courant[3].vitessex = -3.17*24; // km/j
	courant[3].vitessey = 0.1*24; 
	
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
	
	for (int i=0; i<4; i++){
		printf("%d\n",deplacement(ville[i].xville, ville[i].yville,0));
	}
	double volcontinentplast[365];
	int tonneplastarrive[365];
	for (int j=0; j<365; j++){
		tonneplastarrive[j]=0;
	}
	for (int a=0; a<365; a++){
		for (int i=0; i<4; i++){
			for (int j=0; j<ville[i].dechet; j++){
				int timef= deplacement(ville[i].xville, ville[i].yville,0)+a;
				if (timef==999){
					printf("error");
					return 999;
				}
				printf("%d__",timef);
				if (timef<365){
					tonneplastarrive[timef]+=1;
				}
			}
		}
	}
	printf("tableau\n");
	for (int j=0; j<365; j++){
		printf("%d__", tonneplastarrive[j]);
	}
	double x;
	printf("tableau2\n");
	for (int i=1; i<365; i++){
		x=evolutioncont(i, tonneplastarrive,volcontinentplast);
		volcontinentplast[i]=x;
		printf("%f__",x);
	}
	return 0;
}

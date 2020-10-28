#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// random
int randomnb(int max , int min){
	double randomDomaine = RAND_MAX + 1.0;
    int entier1 = (int) (random() / randomDomaine * (abs(max)+abs(min)) +min);
    return entier1;
}
// definition cadre total
int xmax= ;
int ymax= ;

//coordonnées plastiques( definir avec cadre
int xplas= ;
int yplas= ;

// definition courant (on peut pas faire spirale parce que par le vx, vy)
struct courant {
	char * nom;
	int xA;
	int yA;
	int xB;
	int yB;
	int xC;
	int yC;
	int xD;
	int yD;
	float vitessex;
	float vitessey;
}
	
// definition ville
struct ville{
	char * nom;
	int xville;
	int yville;
	float dechet;
	

// spirale (quand la particule rentre dans la zonespi)
// probleme: car quand rentre peut en suite sortir donc il faut dire quand rentre sort plus JAMAIS
int xAspi= ;
int yAspi= ;
int xBspi= ;
int yBspi= ;
int xCspi= ;
int yCspi= ;
int xDspi= ;
int yDspi= ;
float distspi=(x-xplas)*(x-xplas)+(y-yplas)*(y-yplas);
float anglespi=ArcCos((x-xplas)/distspi);
while (x!=xplas) {
	distspi-= //fonc de diminution de r;
	anglespi -= M_PI/10;
	x= distspi*cos(anglespi);
	y= distspi*sin(anglespi);
}
	// il faut aussi compter le temps et definir une fonction r qui diminue de - en - vite
		
//defintion de r= rayon en fonction de la degradation du plastique





// A. Propagation d'un paquet (x, y, r)
void simulePaquet(double x, double y, double r) {
    for (int i = 0; i < 1000; i++) {
        // Vent
        double ventX = 10;
        double ventY = -0.001 * (x - 2000);

        // Aléa
        double ax = randomNumber(30) - 15;
        double ay = randomNumber(30) - 15;

        // Déplacer le paquet
        x += ventX + ax;
        y += ventY + ay;
        r += 20 / r;

        // C. Capteurs
        for (int s = 0; s < 6; s++) {
            double dx = x - capteurs[s].x;
            double dy = y - capteurs[s].y;
            double distance2 = dx * dx + dy * dy;
            if (distance2 < r * r) {
                capteurs[s].paquets += 1;
            }
        }

        // Paquet toujours dans la zone d'intérêt?
        if (x < 0) break;
        if (y < 0) break;
        if (x > 8000) break;
        if (y > 5000) break;
    }

    // Pour la verification d'un paquet
    // printf("%f %f %f\n", x, y, r);
}

double plausibilite(double detectionsSimulees, double detectionsObservees) {
    double difference = detectionsSimulees - detectionsObservees;
    double variance = detectionsSimulees;
    if (variance < 0.0001) variance = 0.0001;
    return exp(-difference * difference / (2 * variance));
}

double simulePaquets(double x, double y, double r, int iterations) {
    // Remettre les compteurs à 0
    for (int i = 0; i < 6; i++) {
        capteurs[i].paquets = 0;
    }

    // Simuler des paquets
    for (int i = 0; i < iterations; i++) {
        simulePaquet(x, y, r);
    }

    // E. Calcul de la plausibilite
    double p = 1;
    for (int i = 0; i < 6; i++) {
        double paquetsParIteration = (double) capteurs[i].paquets / iterations;
        p *= plausibilite(paquetsParIteration, capteurs[i].observation);
    }

    return p;
}

int main(int argc, char * argv[]) {
    srandom(time(NULL));

    // B. Capteurs
    capteurs[0].x = 7340;
    capteurs[0].y = 4020;
    capteurs[0].observation = 0;

    capteurs[1].x = 7500;
    capteurs[1].y = 2880;
    capteurs[1].observation = 0;

    capteurs[2].x = 7420;
    capteurs[2].y = 1910;
    capteurs[2].observation = 3.0;

    capteurs[3].x = 7250;
    capteurs[3].y = 1340;
    capteurs[3].observation = 0;

    capteurs[4].x = 7380;
    capteurs[4].y = 720;
    capteurs[4].observation = 0;

    capteurs[5].x = 6200;
    capteurs[5].y = 280;
    capteurs[5].observation = 0;

    // D. Un point
    double p = simulePaquets(2500, 3100, 10, 100);
    for (int i = 0; i < 6; i++) {
        printf("S%d  %d paquets\n", i, capteurs[i].paquets);
    }

    printf("Plausibilité: %0.5f\n", p);

    // E. Toute la grille
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 40; x++) {
            // C. Simuler
            double p = simulePaquets(100 + x * 200, 4900 - y * 200, 10, 100);

            // F. Affichage
            printf("\x1b[48;5;%dm  ", (int) floor(255 - p * 23));
        }

        printf("\x1b[0m\n");
    }

    return 0;
}

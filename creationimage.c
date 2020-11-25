#include <stdio.h>
#include <stdlib.h>

void creationimage(double * x, double * y, int longueur){
	for (int i=0; i<longueur; i++){
		// Ouvrir un fichier pour l'écrire ("w"),
		char nomfichiersvg[100];
		sprintf(nomfichiersvg, "image-%d.svg",i);
		FILE * fichier = fopen(nomfichiersvg, "w");

		// Ecrire
		fprintf(fichier, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
		fprintf(fichier,"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"641\" height=\"305\" version=\"1.1\" xml:space=\"preserve\">\n");
		fprintf(fichier,"\n");
		fprintf(fichier,"<!-- Fond -->\n");
		fprintf(fichier,"<rect style=\"fill:#0080FF\" width=\"641\" height=\"305\" x=\"0\" y=\"0\" />\n");
		fprintf(fichier,"\n");
		fprintf(fichier,"<!-- cotes -->\n");
		fprintf(fichier,"<path style=\"fill:#DBA901\" d=\"M 641 1 C 619 -116 634 55 641 294\" />\n");
		fprintf(fichier,"<path style=\"fill:#DBA901\" d=\"M -1 182 Q 24 73 1 117\" />\n");
		fprintf(fichier,"\n");
		fprintf(fichier,"<!--villes-->\n");
		fprintf(fichier,"<circle cx=\"641\" cy=\"14\" r=\"5\" fill=\"red\"/>\n");
		fprintf(fichier,"<circle cx=\"641\" cy=\"74\" r=\"5\" fill=\"red\"/>\n");
		fprintf(fichier,"<circle cx=\"641\" cy=\"199\" r=\"5\" fill=\"red\"/>\n");
		fprintf(fichier,"<circle cx=\"0\" cy=\"143\" r=\"5\" fill=\"red\"/>\n");
		fprintf(fichier,"<text x=\"570\" y=\"14\" class=\"small\">Vancouver</text>\n");
		fprintf(fichier,"<text x=\"546\" y=\"74\" class=\"small\">San Fransisco</text>\n");
		fprintf(fichier,"<text x=\"550\" y=\"199\" class=\"small\">Los Angeles</text>\n");
		fprintf(fichier,"<text x=\"6\" y=\"143\" class=\"small\">Tokyo</text>\n");
		fprintf(fichier,"\n");
		fprintf(fichier,"<!--particule-->\n");
		fprintf(fichier,"<circle cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"green\"/>\n", x[i], (305-y[i]));
		fprintf(fichier,"\n");
		fprintf(fichier,"</svg>\n");

		// Fermer le fichier
		fclose(fichier);
		char nomfichierpng[100];
		sprintf(nomfichierpng, "image-%d.png",i);
		char ink[100];
		sprintf(ink,"Inkscape --export-png=%s %s",nomfichierpng, nomfichiersvg);
		system(ink);
	}
}

int main(int argc, char * argv[]){
	double x[]={641, 620, 610, 600, 550};
	double y[]={290, 290, 290, 290, 290};
	creationimage(x, y, 5);
	system("ffmpeg -f image2 -framerate 15 -i image-%05d.png video.avi");
	return 0;
}
	




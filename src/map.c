#include "map.h"

int createMap(FILE* file_itd, Map* map){
	//init variables
	int i;
	int version;
	long position;
	char code[5];


	fscanf(file_itd, "%d\n", &version);
	fgets(code, 5, file_itd);
	
	/*Vérif premiere ligne ex: @ITD 1*/
	if (strcmp(code, "@ITD") !=0){
		fprintf(stderr, "Erreur fichier itd: code @ITD\n");
		return 0;
	}
	if(version<1){
		fprintf(stderr, "Erreur fichier itd: version %d inexistante\n", version);
		return 0;
	}

	/*Vérif premiere ligne ex: carte fichier.ppm*/
	int red=0, blue=0, green=0;
	char keyword[10];

	//test carte
	fgets(keyword, 7, file_itd);
	if(strcmp(keyword, "carte ")!=0){
		fprintf(stderr, "Erreur fichier itd: keyword different de carte\n");
		return 0;
	}
	//format ppm
	char name[25];
	fgets(name, 25, file_itd);
	char* format=strchr(name,'.');
	if (strcmp(format, ".ppm\n")!=0){
		fprintf(stderr, "Erreur fichier itd: autre format que ppm\n");
		return 0;
	}
	else (*map).image=name;

	//test chemin
	fgets(keyword, 8, file_itd);
	if(strcmp(keyword, "chemin ")==0){
		fscanf(file_itd, "%d %d %d\n", &red, &green, &blue);
		if (red<0 || red>255 || green<0 || green>255 ||blue<0 || blue>255){
			fprintf(stderr, "Erreur fichier itd: couleur chemin\n");
			return 0;
		}
		else
			(*map).pathColor=colorRGB(red,green,blue);
	}
	else {
		fprintf(stderr, "Erreur fichier itd: keyword different chemin\n");
		return 0;
	}

}
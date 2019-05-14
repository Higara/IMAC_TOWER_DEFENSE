#include "map.h"

int createMap(FILE* file_itd, Map* map){
	//init variables
	int i;
	int version;
	long position;
	char code[5];


	fscanf(file_itd, "%d\n", &version);
	fgets(code, 5, file_itd);
	
	//Vérif premiere ligne ex: @ITD 1
	if (strcmp(code, "@ITD") !=0){
		fprintf(stderr, "Erreur fichier itd: code @ITD\n");
		return 0;
	}
	if(version<1){
		fprintf(stderr, "Erreur fichier itd: version %d inexistante\n", version);
		return 0;
	}

	//Reste des lignes
	int value1=0, value2=0, value3=0;
	char keyword[10];
	
}
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int createMap(FILE* file_itd, Map* map){
	int i;
	int version;
	char code[5];
	fscanf(file_itd, "%d\n", &version);
	fgets(code, 5, file_itd);
	
	//Vérif premiere ligne 
	if (strcmp(code, "@ITD") !=0){
		fprintf(stderr, "Erreur fichier itd [@ITD code]\n");
		return 0;
	}
	if(version<1){
		fprintf(stderr, "Erreur fichier itd [version]\n");
		return 0;
	}

	//Reste des lignes
	int value1=0, value2=0, value3=0;
	char 
}
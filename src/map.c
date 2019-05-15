#include "map.h"

int createMap(FILE* file_itd, Map* map){
	//init variables
	int i=0;
	int nbNode;
	int version;
	long position;
	int nbLines=0;
	char code[5];
	char name[25];
	int lenght=strlen(name);
	int x,y;


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
	unsigned int red=0, blue=0, green=0;
	char keyword[10];

	//test carte
	fgets(keyword, 7, file_itd);
	if(strcmp(keyword, "carte ")!=0){
		fprintf(stderr, "Erreur fichier itd: keyword different de carte\n");
		return 0;
	}
	//format ppm
	
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
	//test noeud
	fgets(keyword, 7, file_itd);
	if (strcmp(keyword, "noeud ")==0){
		fscanf(file_itd, "%d %d %d\n", &red, &green, &blue);
		if (red<0 || red>255 || green<0 || green>255 ||blue<0 || blue>255){
			fprintf(stderr, "Erreur fichier itd: couleur noeud\n");
			return 0;
		}
		else 
			(*map).nodeColor=colorRGB(red,green,blue);
	}
	else{
		fprintf(stderr, "Erreur fichier itd: keyword different de noeud\n");
		return 0;
	}
	//test construct
	fgets(keyword, 11, file_itd);
	if (strcmp(keyword, "construct ")==0){
		fscanf(file_itd, "%d %d %d\n", &red, &green, &blue);
		if (red<0 || red>255 || green<0 || green>255 ||blue<0 || blue>255){
			fprintf(stderr, "Erreur fichier itd: couleur construct\n");
			return 0;
		}
		else 
			(*map).buildingAreaColor=colorRGB(red,green,blue);
	}
	else{
		fprintf(stderr, "Erreur fichier itd: keyword different de noeud\n");
		return 0;
	}
	//test construct
	fgets(keyword, 4, file_itd);
	if (strcmp(keyword, "in ")==0){
		fscanf(file_itd, "%d %d %d\n", &red, &green, &blue);
		if (red<0 || red>255 || green<0 || green>255 ||blue<0 || blue>255){
			fprintf(stderr, "Erreur fichier itd: couleur entree\n");
			return 0;
		}
		else 
			(*map).inColor=colorRGB(red,green,blue);
	}
	else{
		fprintf(stderr, "Erreur fichier itd: keyword different de in\n");
		return 0;
	}
	//test construct
	fgets(keyword, 5, file_itd);
	if (strcmp(keyword, "out ")==0){
		fscanf(file_itd, "%d %d %d\n", &red, &green, &blue);
		if (red<0 || red>255 || green<0 || green>255 ||blue<0 || blue>255){
			fprintf(stderr, "Erreur fichier itd: couleur sortie\n");
			return 0;
		}
		else 
			(*map).outColor=colorRGB(red,green,blue);
	}
	else{
		fprintf(stderr, "Erreur fichier itd: keyword different de out\n");
		return 0;
	}

	/*recup infos*/
	fscanf(file_itd, "%d\n", &nbNode);
	position=ftell(file_itd);
	while (fgetc(file_itd)!=EOF){
		if(fgetc(file_itd)=='\n')
			nbLines++;
	}
	nbLines++;
	if(nbLines != nbNode){
		fprintf(stderr, "Erreur fichier itd: Nombre noeud\n");
		return 0;
	}
	else 
		(*map).nbNodes=nbNode;


	/*traitement des noeuds*/
	fseek(file_itd, position, SEEK_SET);

	name[lenght-1]='\0';
	char file[30]="images/";
	strcat(file, name);
	SDL_Surface* image=IMG_Load(file);
	if (image==NULL){
		fprintf(stderr, "Erreur fichier itd: chargement image %s\n", file);
		return 0;
	}

	/*Verif*/
	while(i<nbLines){
		fscanf(file_itd, "%d %d\n", &x, &y);
		if (x>image->w || y>image->h || x<0 || y<0){
			fprintf(stderr, "Erreur fichier itd: coordonnées\n");
			return 0;
		}
		i++;
	}
	x=y=0;
	fseek(file_itd, position, SEEK_SET);
	fscanf(file_itd, "%d %d\n", &x, &y);
	Node* now=createNode(x,y);
	Node* first=now;
	for(i=1;i<nbLines;i++){
		fscanf(file_itd,"%d %d\n", &x,&y);
		Node* node=createNode(x,y);
		(*now).next=node;
		now=(*now).next;
	}
	(*now).next=NULL;
	(*map).listNodes=first;

	SDL_FreeSurface(image);

	return 1;
}

Map loadMap(char* ITDname){
	FILE* file_itd=fopen(ITDname, "r");
	Map map;
	if(ITDname == NULL){
		fprintf(stderr, "Erreur ouverture itd: %s\n",ITDname);
		exit(1);
	}
	if(createMap(file_itd, &map))
		return map;
	else{
		fprintf(stderr, "Erreur fichier itd invalide: %s\n",ITDname);
		exit(1);
	}
}
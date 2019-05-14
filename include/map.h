#ifndef ITD_MAP___
#define ITD_MAP___


#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>
#include "extra.h"

typedef struct map {
	char* image; 
	Color nodeColor;
	Color pathColor;
	Color buildingAreaColor;
	Color inColor;
	Color outColor;
	unsigned int nbNodes;
	Node* listNodes;
}Map;

int createMap(FILE* file_itd, Map* map);

#endif
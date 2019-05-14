#ifndef ITD_EXTRA__
#define ITD_EXTRA__
#include <stdlib.h>
#include <stdio.h>

/*COLOR*/
typedef struct str_color3ub{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Color;

Color ColorRGB(float r, float g, float b);

/*Node*/
typedef struct str_node{
	float x;
	float y;
	struct str_node* next;
} Node;

Node* createNode(int x, int y);

/*Position*/
typedef struct str_position{
	float x;
	float y;
} Position;

/*List*/
typedef struct str_list{
	unsigned int size;
	int value;
	Node* previous;
	Node* next;
} List;

#endif
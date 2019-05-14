#include "extra.h"

Color colorRGB(unsigned int r, unsigned int g, unsigned int b) {
	Color newColor;
	newColor.r = r;
	newColor.g = g;
	newColor.b = b;

	return newColor;
}

Node* createNode(int x,int y){
	Node* node=(Node*)malloc(sizeof(Node));
	if (node==NULL){
		fprintf(stderr, "Noeud Nul");
		exit(1);
	}
	(*node).x=x;
	(*node).x=y;
	(*node).next=NULL;
	return node;
}
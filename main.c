#include <stdio.h>
#include <stdlib.h>
#include "const.h"

/*** Struct Constructors and Destructors ***/


/* Node Constructor */
Node * new_Node (const short i, const short j) {

	Node * this_node;
	short halfsize;

	if (debug_on)
		printf("allocating %hd, %hd\n", i, j);

	this_node = (Node *) malloc(sizeof(Node));
	halfsize = SIZE / 2;

	ROW = i;
	COL = j;
	VISITED = FALSE;

	/* Initializing the flood value at this coord
	   NOTE : Right now this only works when SIZE is even -- which is ok */
	if (i < halfsize && j < halfsize)
		FLOODVAL = (halfsize - 1 - i) + (halfsize - 1 - j) ;
			
	else if (i < halfsize && j >= halfsize)
		FLOODVAL = (halfsize - 1 - i) + (j - halfsize) ;
			
	else if (i >= halfsize && j < halfsize)
		FLOODVAL = (i - halfsize) + (halfsize - 1 - j) ;

	else
		FLOODVAL = (i - halfsize) + (j - halfsize) ;

	return this_node;
}


/* Maze Constructor */
Maze * new_Maze () {

	Maze * this_maze;
	short i, j;
	
	this_maze = (Maze *) malloc(sizeof(Maze));

	/* Allocate a new Node for each coord of maze */
	for (i = 0; i < SIZE; ++i) 
		for (j = 0; j < SIZE; ++j) 
			MAPIJ = new_Node (i, j);

	/* setting the neighbors ptrs... must be done after all cells allocated */
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			MAPIJ->left = (j == 0) ? NULL : (this_maze->map[i][j-1]);
			MAPIJ->right = (j == SIZE-1) ? NULL : (this_maze->map[i][j+1]);
			MAPIJ->up = (i == 0) ? NULL : (this_maze->map[i-1][j]);
			MAPIJ->down = (i == SIZE-1) ? NULL : (this_maze->map[i+1][j]);
		}

	return this_maze;
}


/* Node Destructor */
void delete_Node (Node ** npp) {
	
	/* debug statements */
	if (debug_on) 
		printf("deallocating %d, %d\n", (*npp)->row, (*npp)->column);

	free (*npp);
	*npp = 0;
}

/* Maze Destructor */
void delete_Maze (Maze ** mpp) {

	short i, j;

	for (i = 0; i < SIZE; i++) 
		for (j = 0; j < SIZE; j++) 
			delete_Node (&((*mpp)->map[i][j])); 
		
	free(*mpp);
	*mpp = 0;
}

void print_maze(const Maze *this_maze) {
	short x, y;

	printf("\n%s\n\n", "Current Map Values: ");

	//prints out the flood values of each cell in the maze
	for (x = 0; x < SIZE; ++x) {
		for (y = 0; y < SIZE; ++y) {
			printf("%s%3hd", " ", this_maze->map[x][y]->floodval);
		}
		printf("\n\n");
	}

	printf("\n");
}


int main(void) {
  Maze* m=new_Maze();
  print_maze(m);
  return 0;
}
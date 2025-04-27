#pragma once
#define ROWS 20
#define COLUMNS 10

struct point{
// top left is x:0, y:0
// x defines the column, y the row
  int x; 
  int y;
};

struct block{
  int blockType; // blocktype is just the number in blocks.h
  int dimension; // dimension is also the number in blocks.h. tldr: max height/width of the block
  int flat[5][5]; // how the block looks like when it spawns
  int ninety[5][5]; // rotated clockwise by 90 degrees
  int inverted[5][5]; // rotated clockwise by 180 degrees
  int twoseventy[5][5]; // rotated clockwise by 270 degrees
};

struct dataStream{
  int gameFrame[ROWS][COLUMNS]{0}; // ALREADY STATIC BLOCKS AKA HAVE HIT SOMETHING
  int fallingFrame[ROWS][COLUMNS]{0}; // CURRENTLY FALLING FRAME
  int entireGame[ROWS][COLUMNS]{0}; // Both static and moving blocks combined
  point blockNullPoint; // x, y coordinates of the top left corner of the block definition
  unsigned int blockOrientation; // counter for keeping count of the orientation. ++ when rotating right, -- when rotating left. (thats why unsigned)
  block blockType; // blocktype again just the number in blocks.h.
  block nextBlock;
  block nextNextBlock;
  block holdingBlock;
  unsigned long score{0};
};

bool hasHitRockBottom(dataStream frameData); // returns true if the currently falling block has hit something

void printMatrix(int matrix[ROWS][COLUMNS]); // prints out either the currently falling blocks' matrix or the locked blocks matrix. 

void lockFallingBlock(dataStream& frameData); // locks the falling block into the locked blocks' matrix. Used if hasHitRockBottom returns true.

void clearFallingBlock(dataStream& frameData); // clears the falling blocks' frame. Used after lockFallingBlock function.

void addFallingBlock(dataStream& frameData, block block); // adds a new falling block to the falling matrix.

int fallFurtherDown(dataStream& frameData); // moves the falling block down one frame. Automatically checks for collisions

void rotateBlockRight(dataStream& frameData); // rotates block clockwise 90 degrees. Doesn't check for collisions yet.

void rotateBlockLeft(dataStream& frameData); // rotates block anticlockwise 90 degrees. Doesn't check for collisions yet.

void moveBlockRight(dataStream& frameData); // moves block to the right. Checks for OOB

void moveBlockLeft(dataStream& frameData); // moves block to the left. Checks for OOB

void printAllOfGame(dataStream& ds); // prints the game matrix, complete with the falling block and static blocks.

void combineFrames(dataStream& ds); // combines falling and game frame

bool willCollide(const dataStream& frameData, const int matrix[5][5]); // checks if given frame will collide with the game frame
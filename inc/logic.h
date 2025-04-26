#pragma once
#define ROWS 20
#define COLUMNS 10

struct point{
  int x;
  int y;
};

struct block{
  int blockType;
  int dimension;
  int flat[5][5];
  int ninety[5][5];
  int inverted[5][5];
  int twoseventy[5][5];
};

struct dataStream{
  int gameFrame[ROWS][COLUMNS]{0}; // ALREADY STATIC BLOCKS AKA HAVE HIT SOMETHING
  int fallingFrame[ROWS][COLUMNS]{0}; // CURRENTLY FALLING FRAME
  point blockNullPoint;
  unsigned int blockOrientation;
  block blockType;
};

bool hasHitRockBottom(dataStream frameData);

void printMatrix(int matrix[ROWS][COLUMNS]);

void lockFallingBlock(dataStream& frameData);

void clearFallingBlock(dataStream& frameData);

void addFallingBlock(dataStream& frameData, block block);

int fallFurtherDown(dataStream& frameData);

void rotateBlockRight(dataStream& frameData);

void rotateBlockLeft(dataStream& frameData);

void moveBlockRight(dataStream& frameData);

void moveBlockLeft(dataStream& frameData);

void printAllOfGame(const dataStream& ds);
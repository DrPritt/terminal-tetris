#pragma once

#define ROWS 5
#define COLUMNS 4

struct dataStream{
  int gameFrame[ROWS][COLUMNS]{0};
  int fallingFrame[ROWS][COLUMNS]{0};
  long unsigned int score;
  int nextObj[4][5];
};

void genNewNext();

void increaseScore();

bool hasHitRockBottom(dataStream frameData);
#include "../inc/logic.h"
#include <iostream>
#include <cstring>

bool hasHitRockBottom(const dataStream frameData){ // i have hit rock bottom
  // checks whether the falling frame has hit anything and should be stopped from moving any further down
  for(int i{0}; i < ROWS; i++){
    for(int j{0}; j < COLUMNS; j++){
      if(i == (ROWS - 1) && frameData.fallingFrame[i][j]){ return true; } // rangecheck, if any point of the falling block has hit the bottom
      if(frameData.fallingFrame[i][j] && frameData.gameFrame[i+1][j]){ // if theres anything under any of the falling block's coordinates
        return true;
      }
    }
  }
  return false;
}

int fallFurtherDown(dataStream& frameData){
  // moves the falling block one row further down
  if(hasHitRockBottom(frameData)){ return 1; } // DO NOT LET A STOPPED BLOCK FALL ANY FURTHER

  frameData.blockNullPoint.y++;
  std::memmove(frameData.fallingFrame[1], frameData.fallingFrame[0], (ROWS - 1) * sizeof(frameData.fallingFrame[0]));
  // moves everything one row further down (no data loss since wouldn't happen if anything on the last row)
  for(int i{0}; i < COLUMNS; i++){ // sets first row to 0
    frameData.fallingFrame[0][i] = 0;
  }
  return 0;
}

void rotateBlockRight(dataStream& frameData){
  // ROTATES THE FALLING BLOCK RIGHT BY 90 DEGREES
  // DOES NOT CHECK FOR COLLISIONS!!!!!!!!!!!!!
  clearFallingBlock(frameData);
  frameData.blockOrientation++;
  for(int i{0}; i < frameData.blockType.dimension; i++){
    for(int j{0}; j < frameData.blockType.dimension; j++){
      if(frameData.blockOrientation%4 == 0){
      frameData.fallingFrame[i + frameData.blockNullPoint.y][j + frameData.blockNullPoint.x] = frameData.blockType.flat[i][j];
      }else if(frameData.blockOrientation%4 == 1){
        frameData.fallingFrame[i + frameData.blockNullPoint.y][j + frameData.blockNullPoint.x] = frameData.blockType.ninety[i][j];
      }else if(frameData.blockOrientation%4 == 2){
        frameData.fallingFrame[i + frameData.blockNullPoint.y][j + frameData.blockNullPoint.x] = frameData.blockType.inverted[i][j];
      }else if(frameData.blockOrientation%4 == 3){
        frameData.fallingFrame[i + frameData.blockNullPoint.y][j + frameData.blockNullPoint.x] = frameData.blockType.twoseventy[i][j];
      }
    }
  }
}

void rotateBlockLeft(dataStream& frameData){
  // ROTATES THE FALLING BLOCK LEFT BY 90 DEGREES
  // DOES NOT CHECK FOR COLLISIONS!!!!!!!!!!!!!
  clearFallingBlock(frameData);
  frameData.blockOrientation--;
  for(int i{0}; i < frameData.blockType.dimension; i++){
    for(int j{0}; j < frameData.blockType.dimension; j++){
      if(frameData.blockOrientation%4 == 0){
      frameData.fallingFrame[i + frameData.blockNullPoint.y][j + frameData.blockNullPoint.x] = frameData.blockType.flat[i][j];
      }else if(frameData.blockOrientation%4 == 1){
        frameData.fallingFrame[i + frameData.blockNullPoint.y][j + frameData.blockNullPoint.x] = frameData.blockType.ninety[i][j];
      }else if(frameData.blockOrientation%4 == 2){
        frameData.fallingFrame[i + frameData.blockNullPoint.y][j + frameData.blockNullPoint.x] = frameData.blockType.inverted[i][j];
      }else if(frameData.blockOrientation%4 == 3){
        frameData.fallingFrame[i + frameData.blockNullPoint.y][j + frameData.blockNullPoint.x] = frameData.blockType.twoseventy[i][j];
      }
    }
  }
}

void moveBlockRight(dataStream& frameData){
  for(int i{0}; i < ROWS; i++){ 
    if(frameData.fallingFrame[i][COLUMNS-1]){ return; } // CHECKS IF OOB
  }
  if(frameData.blockNullPoint.x != COLUMNS - 1 - frameData.blockType.dimension){
    frameData.blockNullPoint.x++;
  }
  for(int i{0}; i < ROWS; i++){
    std::memmove(&frameData.fallingFrame[i][1], &frameData.fallingFrame[i][0], sizeof(int) * (COLUMNS-1));
    frameData.fallingFrame[i][0] = 0;
  }
}

void moveBlockLeft(dataStream& frameData){
  for(int i{0}; i < ROWS; i++){ 
    if(frameData.fallingFrame[i][0]){ return; } // CHECKS IF OOB
  }
  if(frameData.blockNullPoint.x != 0){
    frameData.blockNullPoint.x--;
  }
  for(int i{0}; i < ROWS; i++){
    std::memmove(&frameData.fallingFrame[i][0], &frameData.fallingFrame[i][1], sizeof(int) * (COLUMNS-1));
    frameData.fallingFrame[i][COLUMNS-1] = 0;
  }
}

void addFallingBlock(dataStream& frameData, block block){
  // adds a falling block to the top of the game
  for(int i{0}; i < block.dimension; i++){
    for(int j{0}; j < block.dimension; j++){
      frameData.fallingFrame[i][j] = block.flat[i][j];
    }
  }
  frameData.blockNullPoint.x = 0;
  frameData.blockNullPoint.y = 0;
  frameData.blockType = block;
}

void clearFallingBlock(dataStream& frameData){
  // clears falling block matrix
  memset(frameData.fallingFrame, 0, sizeof(frameData.fallingFrame));
}

void lockFallingBlock(dataStream& frameData){
  // adds the falling block into locked frames
  for(int i{0}; i < ROWS; i++){
    for(int j{0}; j < COLUMNS; j++){
      if(frameData.fallingFrame[i][j]){
        frameData.gameFrame[i][j] = 1;
      }
    }
  }
}

void printMatrix(int matrix[ROWS][COLUMNS]){
  // just prints out a matrix for debugging
  for(int i{0}; i < ROWS; i++){
    for(int j{0}; j < COLUMNS; j++){
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

void printAllOfGame(const dataStream& ds){
  for(int i{0}; i < ROWS; i++){
    for(int j{0}; j < COLUMNS; j++){
      if(ds.fallingFrame[i][j] || ds.gameFrame[i][j]){
        std::cout << '1' << ' ';
      }else{
        std::cout << '0' << ' ';
      }
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}


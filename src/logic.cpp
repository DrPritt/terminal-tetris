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

  std::memmove(frameData.fallingFrame[1], frameData.fallingFrame[0], (ROWS - 1) * sizeof(frameData.fallingFrame[0]));
  // moves everything one row further down (no data loss since wouldn't happen if anything on the last row)
  for(int i{0}; i < COLUMNS; i++){ // sets first row to 0
    frameData.fallingFrame[0][i] = 0;
  }
  return 0;
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

#ifdef FALLFURTHERTEST
int main(){
  std::cout << "~~~~~~~FALL FURTHER TEST~~~~~~~" << std::endl << std::endl;
  dataStream ds;
  ds.fallingFrame[0][1] = 1;
  while(true){
    printMatrix(ds.fallingFrame);
    if(fallFurtherDown(ds)){ break; }
  }
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  return 0;
}
#endif

#ifdef ROCKBOTTOMTEST
int main(){
  std::cout << "~~~~~~~ROCK BOTTOM TEST~~~~~~~" << std::endl;

  // TEST 2
  // adds blocks to the bottom game frame and one above it for the falling block frame, then tests if they touch. return true
  dataStream ds;
  for(int i{0}; i < COLUMNS; i++){
    ds.gameFrame[ROWS-1][i] = 1;
    ds.fallingFrame[ROWS-2][i] = 1;
  }
  std::cout << "test 1: SHOULD RETURN true: " << std::boolalpha << hasHitRockBottom(ds) << std::endl;

  // TEST 2
  // removes the blocks from bottom game frame. Falling block can fall further without touching. return false!
  for(int i{0}; i < COLUMNS; i++){ 
    ds.gameFrame[ROWS-1][i] = 0;
  }
  std::cout << "test 2: SHOULD RETURN false: " << std::boolalpha << hasHitRockBottom(ds) << std::endl;

  // TEST 3
  // generates a single falling block on the bottom row. should not be able to fall any further. return true!
  dataStream ds2;
  ds2.fallingFrame[ROWS-1][1] = 1; 
  std::cout << "test 3: SHOULD RETURN true: " << std::boolalpha << hasHitRockBottom(ds2) << std::endl;

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}
#endif
#include "../inc/logic.h"

// dataStream newGameTick(){
  // 
// }

bool hasHitRockBottom(dataStream frameData){ // i have hit rock bottom
  for(int i{0}; i < ROWS; i++){
    for(int j{0}; j < COLUMNS; j++){
      if(i == ROWS - 1 && frameData.fallingFrame[i][j]){ return true; } // rangecheck, if any point of the falling block has hit the bottom
      if(frameData.fallingFrame[i][j] && frameData.gameFrame[i+1][j]){ // if theres anything under any of the falling block's coordinates
        return true;
      }
    }
  }
  return false;
}
#include "../inc/logic.h"
#include "../inc/blocks.h"
#include <iostream>
#include <cstring>

void fallFurtherTest() {
  std::cout << "~~~~~~~FALL FURTHER TEST~~~~~~~" << std::endl
            << std::endl;
  dataStream ds;
  ds.fallingFrame[0][1] = 1;
  while (true) {
    printMatrix(ds.fallingFrame);
    if (fallFurtherDown(ds)) {
      break;
    }
  }
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void rockBottomTest() {
  std::cout << "~~~~~~~ROCK BOTTOM TEST~~~~~~~" << std::endl;

  // TEST 2
  // adds blocks to the bottom game frame and one above it for the falling block frame, then tests if they touch. return true
  dataStream ds;
  for (int i{0}; i < COLUMNS; i++) {
    ds.gameFrame[ROWS - 1][i] = 1;
    ds.fallingFrame[ROWS - 2][i] = 1;
  }
  std::cout << "test 1: SHOULD RETURN true: " << std::boolalpha << hasHitRockBottom(ds) << std::endl;

  // TEST 2
  // removes the blocks from bottom game frame. Falling block can fall further without touching. return false!
  for (int i{0}; i < COLUMNS; i++) {
    ds.gameFrame[ROWS - 1][i] = 0;
  }
  std::cout << "test 2: SHOULD RETURN false: " << std::boolalpha << hasHitRockBottom(ds) << std::endl;

  // TEST 3
  // generates a single falling block on the bottom row. should not be able to fall any further. return true!
  dataStream ds2;
  ds2.fallingFrame[ROWS - 1][1] = 1;
  std::cout << "test 3: SHOULD RETURN true: " << std::boolalpha << hasHitRockBottom(ds2) << std::endl;

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void addNewBlockTest(){
  std::cout << "~~~~~~~~~~~ADD FALLING BLOCK TEST~~~~~~~~~~~\n";
  dataStream ds;
  printMatrix(ds.fallingFrame);
  addFallingBlock(ds, TSquare);
  printMatrix(ds.fallingFrame);
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

}

void lockFallingBlockTest(){
  dataStream ds;
  addFallingBlock(ds, TSquare);
  while(true){
    if(fallFurtherDown(ds)){ break; }
  }
  lockFallingBlock(ds);
  clearFallingBlock(ds);
  addFallingBlock(ds, TSquare);
  while(true){
    if(fallFurtherDown(ds)){ break; }
  }
  printMatrix(ds.gameFrame);
  printMatrix(ds.fallingFrame);
}

void rotateFallingBlockRightTest(){
  dataStream ds;
  addFallingBlock(ds, TSquare);
  printMatrix(ds.fallingFrame);
  rotateBlockRight(ds);
  printMatrix(ds.fallingFrame);
  rotateBlockRight(ds);
  printMatrix(ds.fallingFrame);
  rotateBlockRight(ds);
  printMatrix(ds.fallingFrame);
}

void rotateFallingBlockLeftTest(){
  dataStream ds;
  addFallingBlock(ds, TSquare);
  printMatrix(ds.fallingFrame);
  rotateBlockLeft(ds);
  printMatrix(ds.fallingFrame);
  rotateBlockLeft(ds);
  printMatrix(ds.fallingFrame);
  rotateBlockLeft(ds);
  printMatrix(ds.fallingFrame);
}

void moveBlockRightTest(){
  dataStream ds;
  addFallingBlock(ds, TSquare);
  for(int i{0}; i < 9; i++){
    printMatrix(ds.fallingFrame);
    moveBlockRight(ds);
  }
}

void moveBlockLeftTest(){
  dataStream ds;
  addFallingBlock(ds, TSquare);
  for(int i{0}; i < 3; i++){
    printMatrix(ds.fallingFrame);
    moveBlockRight(ds);
  }
  for(int i{0}; i < 6; i++){
    printMatrix(ds.fallingFrame);
    moveBlockLeft(ds);
  }
}

int main(int argv, char *argc[]) {
  for(int i{0}; i < argv; i++){
    if(!strcmp(argc[i], "rockbottom")){
      rockBottomTest();
    }else if(!strcmp(argc[i], "fallfurther")){
      fallFurtherTest();
    }else if(!strcmp(argc[i], "addnewblock")){
      addNewBlockTest();
    }else if(!strcmp(argc[i], "lockfalling")){
      lockFallingBlockTest();
    }else if(!strcmp(argc[i], "rotateblockR")){
      rotateFallingBlockRightTest();
    }else if(!strcmp(argc[i], "rotateblockL")){
      rotateFallingBlockLeftTest();
    }else if(!strcmp(argc[i], "moveblockR")){
      moveBlockRightTest();
    }else if(!strcmp(argc[i], "moveblockL")){
      moveBlockLeftTest();
    }
  }

}
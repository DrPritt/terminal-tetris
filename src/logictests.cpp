// // #include "../inc/logic.h"
// #include "../inc/blocks.h"
// #include <iostream>
// #include <cstring>
// #include <chrono>  // For std::chrono::milliseconds
// #include <thread>  // For std::this_thread::sleep_for
// #include <cstdlib> // For system() call


// void fallFurtherTest() {
//   std::cout << "~~~~~~~FALL FURTHER TEST~~~~~~~" << std::endl
//             << std::endl;
//   dataStream ds;
//   ds.fallingFrame[0][1] = 1;
//   while (true) {
//     printMatrix(ds.fallingFrame);
//     if (fallFurtherDown(ds)) {
//       break;
//     }
//   }
//   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
// }

// void rockBottomTest() {
//   std::cout << "~~~~~~~ROCK BOTTOM TEST~~~~~~~" << std::endl;

//   // TEST 2
//   // adds blocks to the bottom game frame and one above it for the falling block frame, then tests if they touch. return true
//   dataStream ds;
//   for (int i{0}; i < COLUMNS; i++) {
//     ds.gameFrame[ROWS - 1][i] = 1;
//     ds.fallingFrame[ROWS - 2][i] = 1;
//   }
//   std::cout << "test 1: SHOULD RETURN true: " << std::boolalpha << hasHitRockBottom(ds) << std::endl;

//   // TEST 2
//   // removes the blocks from bottom game frame. Falling block can fall further without touching. return false!
//   for (int i{0}; i < COLUMNS; i++) {
//     ds.gameFrame[ROWS - 1][i] = 0;
//   }
//   std::cout << "test 2: SHOULD RETURN false: " << std::boolalpha << hasHitRockBottom(ds) << std::endl;

//   // TEST 3
//   // generates a single falling block on the bottom row. should not be able to fall any further. return true!
//   dataStream ds2;
//   ds2.fallingFrame[ROWS - 1][1] = 1;
//   std::cout << "test 3: SHOULD RETURN true: " << std::boolalpha << hasHitRockBottom(ds2) << std::endl;

//   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
// }

// void addNewBlockTest(){
//   std::cout << "~~~~~~~~~~~ADD FALLING BLOCK TEST~~~~~~~~~~~\n";
//   dataStream ds;
//   printMatrix(ds.fallingFrame);
//   addFallingBlock(ds, TSquare);
//   printMatrix(ds.fallingFrame);
//   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

// }

// void lockFallingBlockTest(){
//   dataStream ds;
//   addFallingBlock(ds, TSquare);
//   while(true){
//     if(fallFurtherDown(ds)){ break; }
//   }
//   lockFallingBlock(ds);
//   clearFallingBlock(ds);
//   addFallingBlock(ds, TSquare);
//   while(true){
//     if(fallFurtherDown(ds)){ break; }
//   }
//   printMatrix(ds.gameFrame);
//   printMatrix(ds.fallingFrame);
// }

// void rotateFallingBlockRightTest(){
//   dataStream ds;
//   addFallingBlock(ds, TSquare);
//   printMatrix(ds.fallingFrame);
//   rotateBlockRight(ds);
//   printMatrix(ds.fallingFrame);
//   rotateBlockRight(ds);
//   printMatrix(ds.fallingFrame);
//   rotateBlockRight(ds);
//   printMatrix(ds.fallingFrame);
// }

// void rotateFallingBlockLeftTest(){
//   dataStream ds;
//   addFallingBlock(ds, TSquare);
//   printMatrix(ds.fallingFrame);
//   rotateBlockLeft(ds);
//   printMatrix(ds.fallingFrame);
//   rotateBlockLeft(ds);
//   printMatrix(ds.fallingFrame);
//   rotateBlockLeft(ds);
//   printMatrix(ds.fallingFrame);
// }

// void moveBlockRightTest(){
//   dataStream ds;
//   addFallingBlock(ds, TSquare);
//   for(int i{0}; i < 9; i++){
//     printMatrix(ds.fallingFrame);
//     moveBlockRight(ds);
//   }
// }

// void moveBlockLeftTest(){
//   dataStream ds;
//   addFallingBlock(ds, TSquare);
//   for(int i{0}; i < 3; i++){
//     printMatrix(ds.fallingFrame);
//     moveBlockRight(ds);
//   }
//   for(int i{0}; i < 6; i++){
//     printMatrix(ds.fallingFrame);
//     moveBlockLeft(ds);
//   }
// }

// void clearScreen() {
//     // Clear screen command for most terminals
//     #ifdef _WIN32
//         system("cls");
//     #else
//         system("clear");
//     #endif
// }

// void testComplexScenarioWithAnimation() {
//     std::cout << "~~~~~~~~~~~COMPLEX SCENARIO TEST~~~~~~~~~~~\n";
//     std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Initial delay
    
//     // Create data stream
//     dataStream ds;
    
//     // Step 1: Summon TSquare
//     clearScreen();
//     std::cout << "Adding TSquare block...\n";
//     addFallingBlock(ds, TSquare);
//     printAllOfGame(ds);
//     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
//     // Step 2: Rotate it twice
//     clearScreen();
//     std::cout << "Rotating TSquare right once...\n";
//     rotateBlockRight(ds);
//     printAllOfGame(ds);
//     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
//     clearScreen();
//     std::cout << "Rotating TSquare right again...\n";
//     rotateBlockRight(ds);
//     printAllOfGame(ds);
//     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
//     // Step 3: Let it fall to the bottom
//     std::cout << "\nLetting TSquare fall to the bottom...\n";
//     while(!hasHitRockBottom(ds)) {
//         clearScreen();
//         std::cout << "Falling TSquare...\n";
//         fallFurtherDown(ds);
//         printAllOfGame(ds);
//         std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Fall speed
//     }
    
//     // Step 4: Lock it in
//     clearScreen();
//     std::cout << "Locking TSquare in place...\n";
//     lockFallingBlock(ds);
//     clearFallingBlock(ds);
//     printAllOfGame(ds);
//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
//     // Step 5: Summon I block
//     clearScreen();
//     std::cout << "Adding Line (I) block...\n";
//     addFallingBlock(ds, Line);
//     printAllOfGame(ds);
//     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
//     // Step 6: Rotate it
//     clearScreen();
//     std::cout << "Rotating Line block right...\n";
//     rotateBlockRight(ds);
//     printAllOfGame(ds);
//     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
//     // Step 7: Move it right while letting it fall
//     std::cout << "\nMoving Line block right while falling...\n";
//     while(true) {
//         // Try to move right if possible
//         bool canMoveRight = true;
//         for(int i{0}; i < ROWS; i++) { 
//             if(ds.fallingFrame[i][COLUMNS-1]) { 
//                 canMoveRight = false;
//                 break;
//             }
//         }
//         if(canMoveRight) {
//             moveBlockRight(ds);
//         }
        
//         // Let it fall
//         if(hasHitRockBottom(ds)) {
//             break;
//         }
//         fallFurtherDown(ds);
        
//         // Display
//         clearScreen();
//         std::cout << "Moving I block right and falling...\n";
//         printAllOfGame(ds);
//         std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Movement speed
//     }
    
//     // Final state
//     clearScreen();
//     std::cout << "Final state:\n";
//     printAllOfGame(ds);
    
//     std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
// }


// // int main(int argv, char *argc[]) {
// //   for(int i{0}; i < argv; i++){
// //     if(!strcmp(argc[i], "rockbottom")){
// //       rockBottomTest();
// //     }else if(!strcmp(argc[i], "fallfurther")){
// //       fallFurtherTest();
// //     }else if(!strcmp(argc[i], "addnewblock")){
// //       addNewBlockTest();
// //     }else if(!strcmp(argc[i], "lockfalling")){
// //       lockFallingBlockTest();
// //     }else if(!strcmp(argc[i], "rotateblockR")){
// //       rotateFallingBlockRightTest();
// //     }else if(!strcmp(argc[i], "rotateblockL")){
// //       rotateFallingBlockLeftTest();
// //     }else if(!strcmp(argc[i], "moveblockR")){
// //       moveBlockRightTest();
// //     }else if(!strcmp(argc[i], "moveblockL")){
// //       moveBlockLeftTest();
// //     }else if(!strcmp(argc[i], "complex")) {
// //       testComplexScenarioWithAnimation();
// //     }
// //   }
// // }


#include <iostream>
#include <unordered_map>
#include <vector>
#include "../include/raylib.h"
#include "../include/codegenerator.h"

int main() {

  //set screen size
  const int screenWidth = 1400;
  const int screenHeight = 700;

  //how bigs are the cells
  const int cellSize = 5;

  //define memory size
  const int memWidth = (int)screenWidth / 2;
  const int memHeight = (int)screenHeight / 2;
  
  const int loopStop = memWidth * memHeight;

  //init memory
  std::vector<std::string> memoryArr;

  //comes from codegenerator.cpp
  initMemory(memoryArr, memWidth , memHeight);

  //-----------------------------------
  //get the colors to draw on window
  std::unordered_map<char, Color> colorsToDraw;
  colorsToDraw['*'] = ORANGE;
  colorsToDraw['+'] = RED;
  colorsToDraw['#'] = SKYBLUE;
  colorsToDraw['@'] = BLUE;
  colorsToDraw['<'] = LIME;
  colorsToDraw['>'] = GREEN;
  colorsToDraw['.'] = BLACK;
  //-----------------------------------



  //--------------------------------------------------
  //--------------------------------------------------
  //--------------------------------------------------
  //raylib rendering code
  InitWindow(screenWidth, screenHeight, "SWP v9 with raylib");
  SetTargetFPS(60);


  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(BLACK);

      // get new frame
      getNewFrame(memoryArr);
      
      //draw loop
      for (int i = 0; i < loopStop; i++){
        int currRow = (int)(i / memWidth); // determines row
        int currColumn = i % memWidth; // determines column

        char instruction = memoryArr[currRow][currColumn];
        DrawRectangle(currColumn * cellSize , currRow * cellSize , cellSize, cellSize, colorsToDraw[instruction]);
      }

    EndDrawing();
  }
  CloseWindow();
  //--------------------------------------------------
  //--------------------------------------------------
  //--------------------------------------------------


  //print ruleset 
  for (auto const& i : ruleSet) {
    for (auto const& j : i.second) {
        std::cout << "main key: " << i.first << " sub key: " << j.first << " value: " << j.second << '\n';
    }
  }

  return 0;
}
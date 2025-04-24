#pragma once
#include "logic.h"

#ifndef TSQUARE
#define TSQUARE
block TSquare = {
  .blockType = 1,
  .dimension = 3,
  .flat = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 0, 0}
  },
  .ninety = {
    {0, 1, 0},
    {0, 1, 1},
    {0, 1, 0}
  },
  .inverted = {
    {0, 0, 0},
    {1, 1, 1},
    {0, 1, 0}
  },
  .twoseventy = {
    {0, 1, 0},
    {1, 1, 0},
    {0, 1, 0}
  }
};
#endif

#ifndef LINE
#define LINE
block Line = {
  .blockType = 2,
  .dimension = 4,
  .flat = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  .ninety = {
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0}
  },
  .inverted = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0}
  },
  .twoseventy = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}
  }
};
#endif
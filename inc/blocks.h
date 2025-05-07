// DEFINE ALL BLOCKS HERE!
// !!!!!INCLUDE THIS FILE ONLY ONCE!!!!!!!!
// BLOCK DEFINITIONS ARE CLOCKWISE
// increase blocktype by 1 (one) each new block
// add your block to the list in the bottom
// dimension is just max width/height of the block
// add header protection for each new definition
// good luck have fun C:
#pragma once
#include "logic.h"
#include "blocks.h"

#define TOTALBLOCKS 7

#ifndef TSquare
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

#ifndef Line
block Line = {
  .blockType = 2,
  .dimension = 4,
  .flat = {
    {0, 0, 0, 0},
    {2, 2, 2, 2},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  .ninety = {
    {0, 0, 2, 0},
    {0, 0, 2, 0},
    {0, 0, 2, 0},
    {0, 0, 2, 0}
  },
  .inverted = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 2, 2, 2},
    {0, 0, 0, 0}
  },
  .twoseventy = {
    {0, 2, 0, 0},
    {0, 2, 0, 0},
    {0, 2, 0, 0},
    {0, 2, 0, 0}
  }
};
#endif

#ifndef Sblock
block Sblock = {
  .blockType = 3,
  .dimension = 3,
  .flat = {
    {0, 3, 3},
    {3, 3, 0},
    {0, 0, 0}
  },
  .ninety = {
    {0, 3, 0},
    {0, 3, 3},
    {0, 0, 3}
  },
  .inverted = {
    {0, 3, 3},
    {3, 3, 0},
    {0, 0, 0}
  },
  .twoseventy = {
    {0, 3, 0},
    {0, 3, 3},
    {0, 0, 3}
  }
};
#endif

#ifndef Zblock
block Zblock = {
  .blockType = 4,
  .dimension = 3,
  .flat = {
    {4, 4, 0},
    {0, 4, 4},
    {0, 0, 0}
  },
  .ninety = {
    {0, 4, 0},
    {4, 4, 0},
    {4, 0, 0}
  },
  .inverted = {
    {4, 4, 0},
    {0, 4, 4},
    {0, 0, 0}
  },
  .twoseventy = {
    {0, 4, 0},
    {4, 4, 0},
    {4, 0, 0}
  }
};
#endif

#ifndef Lblock
block Lblock = {
  .blockType = 5,
  .dimension = 3,
  .flat = {
    {0, 5, 0},
    {0, 5, 0},
    {0, 5, 5}
  },
  .ninety = {
    {0, 0, 5},
    {5, 5, 5},
    {0, 0, 0}
  },
  .inverted = {
    {5, 5, 0},
    {0, 5, 0},
    {0, 5, 0}
  },
  .twoseventy = {
    {5, 5, 5},
    {5, 0, 0},
    {0, 0, 0}
  }
};
#endif

#ifndef Jblock
block Jblock = {
  .blockType = 6,
  .dimension = 3,
  .flat = {
    {0, 6, 0},
    {0, 6, 0},
    {6, 6, 0}
  },
  .ninety = {
    {6, 0, 0},
    {6, 6, 6},
    {0, 0, 0}
  },
  .inverted = {
    {0, 6, 6},
    {0, 6, 0},
    {0, 6, 0}
  },
  .twoseventy = {
    {6, 6, 6},
    {0, 0, 6},
    {0, 0, 0}
  }
};
#endif

#ifndef Oblock
block Oblock = {
  .blockType = 7,
  .dimension = 2,
  .flat = {
    {7, 7},
    {7, 7}
  },
  .ninety = {
    {7, 7},
    {7, 7}
  },
  .inverted = {
    {7, 7},
    {7, 7}
  },
  .twoseventy = {
    {7, 7},
    {7, 7}
  }
};
#endif
block blockList[TOTALBLOCKS]= {TSquare, Line, Sblock, Zblock, Lblock, Jblock, Oblock};
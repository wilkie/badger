#ifndef BADGER_TILE_H
#define BADGER_TILE_H

namespace Badger {
  struct Tile {
    bool         passable;
    bool         destructable;
    unsigned int spriteIndex;
  };
}

#endif

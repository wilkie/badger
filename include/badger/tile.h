#ifndef BADGER_TILE_H
#define BADGER_TILE_H

namespace Badger {
  /*
   *  Defines a tile on the map.
   */
  struct Tile {
    /*
     *  Whether or not the tile can be walked through.
     */
    bool         passable;

    /*
     *  Whether or not the tile can be destroyed.
     */
    bool         destructable;

    /*
     *  The sprite index in the Badger::SpriteSheet to draw for this tile.
     */
    unsigned int spriteIndex;
  };
}

#endif

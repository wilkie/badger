#ifndef BADGER_MAP_H
#define BADGER_MAP_H

#include "badger/tile.h"
#include "badger/sprite_sheet.h"

namespace Badger {
  /*
   *  Describes a world made out of tiles drawn from a single SpriteSheet.
   */
  class Map {
    public:
      /*
       *  Constructs a Badger::Map of the given width and height and drawn
       *    using the given Badger::SpriteSheet
       */
      Map(unsigned int width,
          unsigned int height,
          SpriteSheet* spriteSheet);

      /*
       *  Queries the tile at the world coordinates (x,y)
       */
      Tile*        tile(unsigned int x, unsigned int y);

      /*
       *  Returns the width of the map.
       */
      unsigned int width();

      /*
       *  Returns the height of the map
       */
      unsigned int height();

      /*
       *  Returns the Badger::SpriteSheet being used to draw the map.
       */
      SpriteSheet* spriteSheet();

    private:

      // Internal storage
      unsigned int _width;
      unsigned int _height;
      SpriteSheet* _spriteSheet;

      // The tiles that compose the map
      Tile*        _tiles;

      /*
       * Randomly assigns tiles from _tiles to be walls. Wall tiles use
       * sprites in range 16-19 and are impassable.
       */
      void _generateWalls();
  };
}

#endif

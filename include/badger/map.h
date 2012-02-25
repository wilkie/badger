#ifndef BADGER_MAP_H
#define BADGER_MAP_H

#include "badger/tile.h"
#include "badger/sprite_sheet.h"

namespace Badger {
  class Map {
    private:
      unsigned int _width;
      unsigned int _height;
      Tile*        _tiles;

      SpriteSheet* _spriteSheet;

    public:
      Map(unsigned int width,
          unsigned int height,
          SpriteSheet* spriteSheet);

      Tile*        tile(unsigned int x, unsigned int y);
      unsigned int width();
      unsigned int height();
      SpriteSheet* spriteSheet();
  };
}

#endif

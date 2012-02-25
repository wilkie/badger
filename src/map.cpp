#include "badger/map.h"

#include <string.h>

Badger::Map::Map(unsigned int width,
                 unsigned int height,
                 SpriteSheet* spriteSheet) : 
                   _width(width),
                   _height(height) {
  _tiles = new Tile[_width * _height];
  memset(_tiles, 0, _width*_height*sizeof(Tile));
  for(unsigned int x = 0; x < _width * _height; x++) {
    _tiles[x].spriteIndex = rand() % 5;
  }
  _spriteSheet = spriteSheet;
}

unsigned int Badger::Map::width() {
  return _width;
}

unsigned int Badger::Map::height() {
  return _height;
}

Badger::Tile* Badger::Map::tile(unsigned int x, unsigned int y) {
  return &_tiles[(y * _width) + x];
}

Badger::SpriteSheet* Badger::Map::spriteSheet() {
  return _spriteSheet;
}

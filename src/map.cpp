#include <badger/map.h>

#include <string.h>

Badger::Map::Map(unsigned int width, unsigned int height) : 
  _width(width),
  _height(height) {
	_tiles = new Tile[_width * _height];
	memset(_tiles, 0, _width*_height*sizeof(Tile));
}

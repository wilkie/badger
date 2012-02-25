#include "badger/viewport.h"

Badger::Viewport::Viewport() {
}

void Badger::Viewport::draw(Renderer* renderer) {
  unsigned int x, y;
  renderer->bindTexture(_map->spriteSheet()->texture());
  for (y = 0; y < _map->height(); y++) {
    for (x = 0; x < _map->width(); x++) {
      Tile* tile = _map->tile(x, y);
      double coords[4];
      _map->spriteSheet()->textureCoordinates(tile->spriteIndex, coords);
      renderer->drawSquare(x*32.0f, y*32.0f, 32.0f, 32.0f,
                           coords[0], coords[1], coords[2], coords[3]);
    }
  }
}

Badger::Map* Badger::Viewport::map() {
  return _map;
}

void Badger::Viewport::map(Badger::Map* value) {
  _map = value;
}

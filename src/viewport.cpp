#include "badger/viewport.h"

Badger::Viewport::Viewport() {
}

void Badger::Viewport::draw(Renderer* renderer) {
  unsigned int x, y;
  Map* map = _world->map();

  renderer->bindTexture(map->spriteSheet()->texture());
  for (y = 0; y < map->height(); y++) {
    for (x = 0; x < map->width(); x++) {
      Tile* tile = map->tile(x, y);
      double coords[4];
      map->spriteSheet()->textureCoordinates(tile->spriteIndex, coords);

      Sprite* sprite = map->spriteSheet()->sprite(tile->spriteIndex);
      renderer->drawSquare(x*32.0f, y*32.0f,
                           (float)sprite->width, (float)sprite->height,
                           coords[0], coords[1], coords[2], coords[3]);
    }
  }
}

Badger::World* Badger::Viewport::world() {
  return _world;
}

void Badger::Viewport::world(Badger::World* value) {
  _world = value;
}

#include "badger/viewport.h"

Badger::Viewport::Viewport() {
}

void Badger::Viewport::draw(Renderer* renderer) {
  double coords[4];

  // draw the map
  Map* map = _world->map();
  renderer->bindTexture(map->spriteSheet()->texture());
  for (int y = map->height() - 1; y >= 0; y--) {
    for (int x = 0; x < map->width(); x++) {
      Tile* tile = map->tile(x, y);
      map->spriteSheet()->textureCoordinates(tile->spriteIndex, coords);

      Sprite* sprite = map->spriteSheet()->sprite(tile->spriteIndex);
      renderer->drawSquare(x*32.0f, y*32.0f,
                           (float)sprite->width, (float)sprite->height,
                           coords[0], coords[1], coords[2], coords[3]);
    }
  }

  // draw the actors
  for (int x = 0; x < _world->actorCount(); x++) {
    Badger::Actor* actor = _world->actor(x);
    renderer->bindTexture(actor->spriteSheet()->texture());

    // hard-coding the first sprite (base) for now...
    actor->spriteSheet()->textureCoordinates("down_0", coords);

    Sprite* sprite = actor->spriteSheet()->sprite("down_0");
    renderer->drawSquare((float)actor->position().x, (float)actor->position().y,
                         (float)sprite->width, (float)sprite->height,
                         coords[0], coords[1], coords[2], coords[3]);
  }
}

Badger::World* Badger::Viewport::world() {
  return _world;
}

void Badger::Viewport::world(Badger::World* value) {
  _world = value;
}

#include "badger/viewport.h"

Badger::Viewport::Viewport() {
}

void Badger::Viewport::draw(Renderer* renderer) {
  double coords[4];

  // draw the map
  Map* map = _world->map();
  renderer->bindTexture(map->spriteSheet()->texture());

  // Render all background tiles
  for (long y = map->height() - 1; y >= 0; y--) {
    for (long x = 0; x < (long)map->width(); x++) {
      Tile* tile = map->tile(x, y);
      if (!tile->passable) {
        continue;
      }

      map->spriteSheet()->textureCoordinates(tile->spriteIndex, coords);

      Sprite* sprite = map->spriteSheet()->sprite(tile->spriteIndex);
      renderer->drawSquare(x*32.0f, y*32.0f,
                           (float)sprite->width, (float)sprite->height,
                           coords[0], coords[1], coords[2], coords[3],
                           -1000.0);
    }
  }

  // Render all foreground Tiles
  for (long y = map->height() - 1; y >= 0; y--) {
    for (long x = 0; x < (long)map->width(); x++) {
      Tile* tile = map->tile(x, y);
      if (tile->passable) {
        continue;
      }

      map->spriteSheet()->textureCoordinates(tile->spriteIndex, coords);

      Sprite* sprite = map->spriteSheet()->sprite(tile->spriteIndex);
      renderer->drawSquare(x*32.0f, y*32.0f + (((float)sprite->height - 32.0f) / 2.0f),
                           (float)sprite->width, (float)sprite->height,
                           coords[0], coords[1], coords[2], coords[3],
                           -(double)y*32.0);
    }
  }

  // draw the actors
  for (long x = 0; x < (long)_world->actorCount(); x++) {
    Badger::Actor* actor = _world->actor(x);
    renderer->bindTexture(actor->spriteSheet()->texture());

    // Get texture coordinates for actor
    actor->textureCoordinates(coords);
    Sprite* sprite = actor->sprite();
    renderer->drawSquare((float)actor->position().x, (float)actor->position().y,
                         (float)sprite->width, (float)sprite->height,
                         coords[0], coords[1], coords[2], coords[3],
                         -(float)actor->position().y);
  }
}

Badger::World* Badger::Viewport::world() {
  return _world;
}

void Badger::Viewport::world(Badger::World* value) {
  _world = value;
}

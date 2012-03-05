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
      renderer->drawSquare(x * 32.0, y * 32.0,
                           sprite->width, sprite->height,
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
      renderer->drawSquare(x * 32.0, y * 32.0 + ((sprite->height - 32.0) / 2.0),
                           sprite->width, sprite->height,
                           coords[0], coords[1], coords[2], coords[3],
                           -(double)y * 32.0);
    }
  }

  // draw the actors
  for (long i = 0; i < (long)_world->actorCount(); i++) {
    Badger::Actor* actor = _world->actor(i);
    renderer->bindTexture(actor->spriteSheet()->texture());

    // Get texture coordinates for actor
    actor->textureCoordinates(coords);
    Sprite* sprite = actor->sprite();
    renderer->drawSquare(actor->position().x, actor->position().y,
                         sprite->width, sprite->height,
                         coords[0], coords[1], coords[2], coords[3],
                         -actor->position().y);
  }
}

Badger::World* Badger::Viewport::world() {
  return _world;
}

void Badger::Viewport::world(Badger::World* value) {
  _world = value;
}

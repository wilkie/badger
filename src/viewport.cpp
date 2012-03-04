#include "badger/viewport.h"

Badger::Viewport::Viewport() {
}

void Badger::Viewport::draw(Renderer* renderer) {
  double coords[4];

  // draw the map
  Map* map = _world->map();
  renderer->bindTexture(map->spriteSheet()->texture());

  // Render all background tiles
  for (int y = map->height() - 1; y >= 0; y--) {
    for (int x = 0; x < map->width(); x++) {
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
  for (int y = map->height() - 1; y >= 0; y--) {
    for (int x = 0; x < map->width(); x++) {
      Tile* tile = map->tile(x, y);
      if (tile->passable) {
        continue;
      }

      map->spriteSheet()->textureCoordinates(tile->spriteIndex, coords);

      Sprite* sprite = map->spriteSheet()->sprite(tile->spriteIndex);
      renderer->drawSquare(x*32.0f, y*32.0f + ((sprite->height - 32.0) / 2.0),
                           (float)sprite->width, (float)sprite->height,
                           coords[0], coords[1], coords[2], coords[3],
                           -y*32.0f);
    }
  }

  // draw the actors
  for (int x = 0; x < _world->actorCount(); x++) {
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

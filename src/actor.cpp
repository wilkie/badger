#include "badger/actor.h"

Badger::Actor::Actor(const char* actorFile,
                     SpriteSheet* spriteSheet,
                     unsigned int x,
                     unsigned int y) {
  _spriteSheet = spriteSheet;

  FILE* f = fopen(actorFile, "rt");

  _position.x = x;
  _position.y = y;
  fscanf(f, "%d, %d\n", &_position.width, &_position.height);

}

Badger::SpriteSheet* Badger::Actor::spriteSheet() {
  return _spriteSheet;
}

Badger::Position Badger::Actor::position() {
  return _position;
}

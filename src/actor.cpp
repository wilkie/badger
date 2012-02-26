#include "badger/actor.h"

#include <string.h>

Badger::Actor::Actor(SpriteSheet* spriteSheet) {
  _spriteSheet = spriteSheet;
}

Badger::SpriteSheet* Badger::Actor::spriteSheet() {
  return _spriteSheet;
}

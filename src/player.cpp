#include "badger/player.h"

#include <string.h>

Badger::Player::Player(SpriteSheet* spriteSheet) {
  _spriteSheet = spriteSheet;
}

Badger::SpriteSheet* Badger::Player::spriteSheet() {
  return _spriteSheet;
}

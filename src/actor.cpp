#include "badger/actor.h"
#include <windows.h>

Badger::Actor::Actor(const char* actorFile,
                     SpriteSheet* spriteSheet,
                     unsigned int x,
                     unsigned int y) {
  _spriteSheet = spriteSheet;

  FILE* f = fopen(actorFile, "rt");

  _position.x = x;
  _position.y = y;

  char key[129];
  char val[129];

  while(!feof(f)) {
    fscanf(f, "%128s %128s\n", key, val);
    OutputDebugString(key);
    OutputDebugString(" -> ");
    OutputDebugString(val);
    OutputDebugString("\n");

    if (strcmp(key, "width") == 0) {
      _position.width = atoi(val);
    }
    else if (strcmp(key, "height") == 0) {
      _position.height = atoi(val);
    }
    else if (strcmp(key, "sprites") == 0) {
      _spriteSheet = new SpriteSheet(val);
    }
    else {
      // Animation
    }
  }
}

Badger::SpriteSheet* Badger::Actor::spriteSheet() {
  return _spriteSheet;
}

Badger::Position Badger::Actor::position() {
  return _position;
}

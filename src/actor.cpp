#include "badger/actor.h"

Badger::Actor::~Actor() {
  // Deallocate animations
  for (unsigned int i = 0; i < _animations.size(); i++) {
    for (unsigned int j = 0; j < _animations[i]->frames.size(); j++) {
      delete _animations[i]->frames[j];
    }
    delete _animations[i];
  }
}

Badger::Actor::Actor(const char* actorFile,
                     SpriteSheet* spriteSheet,
                     unsigned int x,
                     unsigned int y) {
  _currentAnimation = NULL;
  _currentFrame = 0;

  _spriteSheet = spriteSheet;

  FILE* f = fopen(actorFile, "rt");

  _position.x = x;
  _position.y = y;

  char key[129];
  char val[129];

  while(!feof(f)) {
    fscanf(f, "%128s %128s\n", key, val);

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

      // Create an animation structure
      Animation* newAnimation = _newAnimation(key);

      // Store all of the sprites
      int spriteIndex = -1;
      do {
        spriteIndex = _spriteSheet->enumerateSprites(val, spriteIndex);
        if (spriteIndex != -1) {
          AnimationFrame* frame = new AnimationFrame;
          _spriteSheet->textureCoordinates(spriteIndex, frame->textureCoordinates);
          newAnimation->frames.push_back(frame);
        }
      } while(spriteIndex != -1);
    }
  }
}

Badger::Animation* Badger::Actor::_newAnimation(const char* name) {
  Animation* ret = new Animation;
  strncpy(ret->name, name, 128);
  _animations.push_back(ret);
  return ret;
}

Badger::SpriteSheet* Badger::Actor::spriteSheet() {
  return _spriteSheet;
}

Badger::Position Badger::Actor::position() {
  return _position;
}

#include "config.h"
#include "badger/actor.h"

// Mocks
Badger::SpriteSheet::SpriteSheet(const char* filename) {}
Badger::SpriteSheet::~SpriteSheet() {}
int Badger::SpriteSheet::enumerateSprites(const char* wildcard, unsigned int last) { return -1; }
Badger::Sprite* Badger::SpriteSheet::sprite(unsigned int index) { return NULL; }
void Badger::SpriteSheet::textureCoordinates(unsigned int index, double coords[4]) { }

#include "harness.h"

describe (Actor) {
  describe (position) {
    it ("should yield the x coordinate specified when it was constructed") {
      Badger::Actor* a = new Badger::Actor("test/files/blob.actor", 42, 24);
      should(a->position().x == 42);
    }

    it ("should yield the y coordinate specified when it was constructed") {
      Badger::Actor* a = new Badger::Actor("test/files/blob.actor", 42, 24);
      should(a->position().y == 24);
    }

    it ("should yield the width described in the given actor file") {
      Badger::Actor* a = new Badger::Actor("test/files/blob.actor", 42, 24);
      should(a->position().width == 16);
    }

    it ("should yield the height described in the given actor file") {
      Badger::Actor* a = new Badger::Actor("test/files/blob.actor", 42, 24);
      should(a->position().height == 11);
    }
  }
}

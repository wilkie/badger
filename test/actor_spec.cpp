#include "badger/actor.h"

#include "config.h"
#include "harness.h"

// Mocks
Badger::SpriteSheet::SpriteSheet(const char* filename) {}
int Badger::SpriteSheet::enumerateSprites(const char* wildcard, unsigned int last) { return -1; }

describe (Actor) {
  describe (position) {
    it ("should yield the x coordinate specified when it was constructed") {
      Badger::Actor* a = new Badger::Actor("test/files/blob.actor", NULL, 42, 24);
      should(a->position().x == 42);
    }

    it ("should yield the y coordinate specified when it was constructed") {
      Badger::Actor* a = new Badger::Actor("test/files/blob.actor", NULL, 42, 24);
      should(a->position().y == 24);
    }

    it ("should yield the width described in the given actor file") {
      Badger::Actor* a = new Badger::Actor("test/files/blob.actor", NULL, 42, 24);
      should(a->position().width == 16);
    }

    it ("should yield the height described in the given actor file") {
      Badger::Actor* a = new Badger::Actor("test/files/blob.actor", NULL, 42, 24);
      should(a->position().height == 11);
    }
  }
}

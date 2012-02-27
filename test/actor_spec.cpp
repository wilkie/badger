#include "harness.h"

#include "../include/badger/actor.h"

describe (Actor) {
  describe (position) {
    it ("should yield the x coordinate described in the given actor file") {
      Actor* a = new Actor("files/blob.actor", NULL, 0, 0);
      should(a->position.x == 16);
    }

    it ("should yield the y coordinate described in the given actor file") {
      Actor* a = new Actor("files/blob.actor", NULL, 0, 0);
      should(a->position.y == 11);
    }
  }
}

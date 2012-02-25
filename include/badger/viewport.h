#ifndef BADGER_VIEWPORT_H
#define BADGER_VIEWPORT_H

#include "badger/world.h"
#include "badger/renderer.h"

namespace Badger {
  /*
   *  Describes a view of the world from a particular position.
   */
  class Viewport {
    public:
      /*
       *  Constructs a Badger::Viewport.
       */
      Viewport();

      /*
       *  Attaches the given Badger::World.
       */
      void world(Badger::World* value);

      /*
       *  Returns the current Badger::World.
       */
      Badger::World* world();

      /*
       *  Draws the world from the perspective of this view with the
       *    given Badger::Renderer.
       */
      void draw(Renderer* renderer);

    private:

      // Internal Storage
      World* _world;
  };
}

#endif

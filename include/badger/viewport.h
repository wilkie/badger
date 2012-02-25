#ifndef BADGER_VIEWPORT_H
#define BADGER_VIEWPORT_H

#include "badger/map.h"
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
       *  Attaches the given Badger::Map.
       */
      void map(Badger::Map* value);

      /*
       *  Returns the current Badger::Map.
       */
      Badger::Map* map();

      /*
       *  Draws the world from the perspective of this view with the
       *    given Badger::Renderer.
       */
      void draw(Renderer* renderer);

    private:

      // Internal Storage
      Map* _map;
  };
}

#endif

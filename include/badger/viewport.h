#ifndef BADGER_VIEWPORT_H
#define BADGER_VIEWPORT_H

#include "badger/map.h"
#include "badger/renderer.h"

namespace Badger {
  class Viewport {
    private:
      Map* _map;

    public:
      Viewport();
      void map(Badger::Map* value);
      Badger::Map* map();
      void draw(Renderer* renderer);
  };
}

#endif

#ifndef BADGER_WORLD_H
#define BADGER_WORLD_H

#include <badger/map.h>

namespace Badger {

  class World {
    public:
      /*
       * Creates a whole new Badger::World!
       */
      World(Badger::Map* map);

      /*
       * Return: the map of the world.
       */
      Badger::Map* map();

    private:

      // the world map
      Map* _map;
  };
}

#endif

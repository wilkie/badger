#include "badger/world.h"

Badger::World::World(Map* map) {
  _map = map;
}

Badger::Map* Badger::World::map() {
  return _map;
}

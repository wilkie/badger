#include "badger/world.h"

Badger::World::World(Map* map) {
  _map        = map;
}

Badger::Map* Badger::World::map() {
  return _map;
}

unsigned int Badger::World::actorCount() {
  return _actors.size();
}

bool Badger::World::addActor(Actor* actor) {
  _actors.push_back(actor);
  return true;
}

Badger::Actor* Badger::World::actor(unsigned int index) {
  return _actors[index];
}

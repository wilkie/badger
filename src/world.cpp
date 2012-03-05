#include "badger/world.h"

Badger::World::World(Map* map) {
  _map        = map;
  _collider   = new ColliderAgent(map);
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

void Badger::World::update(double elapsed) {
  for (unsigned int i = 0; i < _actors.size(); i++) {
    _actors[i]->update(elapsed, _collider);
  }
}

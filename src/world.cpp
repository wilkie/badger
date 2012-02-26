#include "badger/world.h"

Badger::World::World(Map* map) {
  _map        = map;

  _actors     = NULL;
  _actorCount = 0;
  _actorMax   = 128;
}

Badger::Map* Badger::World::map() {
  return _map;
}

unsigned int Badger::World::actorCount() {
  return _actorCount;
}

bool Badger::World::addActor(Actor* actor) {
  if(_actors == NULL) {
    _actors = new Actor*[_actorMax];
    memset(_actors, 0, sizeof(Actor*)*_actorMax);
  }

  if(_actorCount >= _actorMax) {
    _resizeActorArray();
  }

  _actors[_actorCount] = actor;
  _actorCount++;

  return true;
}

Badger::Actor* Badger::World::actor(unsigned int index) {
  return _actors[index];
}

// looks familiar...
void Badger::World::_resizeActorArray() {
  Actor** old = _actors;

  _actors = new Actor*[_actorMax + 128];
  memcpy(_actors, old, sizeof(Actor*)*_actorCount);
  _actorMax += 128;

  delete [] old;
}

#ifndef BADGER_WORLD_H
#define BADGER_WORLD_H

#include <badger/map.h>
#include <badger/actor.h>
#include <badger/collider_agent.h>

#include <vector>

namespace Badger {

  class World {
    public:
      /*
       *  Creates a whole new Badger::World!
       */
      World(Badger::Map* map);

      /*
       *  Return: the map of the world.
       */
      Badger::Map* map();

      /*
       *  Puts the given actor into the world.
       */
      bool addActor(Badger::Actor* actor);

      /*
       *  Return: the actor at the given index.
       */
      Actor* actor(unsigned int index);

      /*
       *  Return: the number of actors currently in the world.
       */
      unsigned int actorCount();

      /*
       *  Updates the world state to represent the elapsed time.
       */
      void update(double elapsed);

    private:
      // The world map
      Map* _map;

      // Collider Agent
      ColliderAgent* _collider;

      // Contains the actors that are fighting for justice
      std::vector<Actor*> _actors;
  };
}

#endif

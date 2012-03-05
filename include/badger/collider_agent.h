#ifndef BADGER_COLLIDER_AGENT_H
#define BADGER_COLLIDER_AGENT_H

#include "badger/map.h"

#include "badger/rectangle.h"
#include "badger/point.h"

namespace Badger {
  class ColliderAgent {
    public:
      ColliderAgent(Map* map);

      /*
       *  Determines how far along the given vector the given Rectangle can
       *  move. Returns true when the Rectangle can move the entire distance. 
       */
      bool move(Rectangle* p, Point* v);

    private:
      Map* _map;
  };
}

#endif

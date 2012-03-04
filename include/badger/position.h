#ifndef BADGER_POSITION_H
#define BADGER_POSITION_H

namespace Badger {

  struct Position {

    // The x and y coordinates of the object's footprint in the world.
    double x;
    double y;

    // The width and height of the object's footprint in the world.
    unsigned int width;
    unsigned int height;
  };

}

#endif

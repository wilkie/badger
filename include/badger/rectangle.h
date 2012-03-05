#ifndef BADGER_RECTANGLE_H
#define BADGER_RECTANGLE_H

#include "badger/line.h"
#include "badger/point.h"

namespace Badger {
  struct Rectangle {
    double x;
    double y;

    double width;
    double height;

    bool intersects(Rectangle* rectangle);
    bool intersects(Line* lines, double* at);

    bool contains(Point* point);
  };
}

#endif

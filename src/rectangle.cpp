#include "badger/rectangle.h"

bool Badger::Rectangle::intersects(Rectangle* rectangle) {
  bool doesNotIntersect = false;
  doesNotIntersect |= rectangle->x > (x + width);
  doesNotIntersect |= x            > (rectangle->x + rectangle->width);
  doesNotIntersect |= rectangle->y > (y + height);
  doesNotIntersect |= y            > (rectangle->y + rectangle->height);
  return !doesNotIntersect;
}

bool Badger::Rectangle::intersects(Line* line, double* t) {
  Rectangle boundingBox;
  boundingBox.width  = (line->points[0].x - line->points[1].x);
  boundingBox.height = (line->points[0].y - line->points[1].y);

  // Liang-Barsky Algorithm to find the intersection point
 
  // Parametric Equation for a Line:
  // x = boundingBox.x + t * (boundingBox.width);
  // y = boundingBox.y + t * (boundingBox.height);
  
  // Use these with the sides of the rectangle to find values of 't'

  // If these are within the range [0..1], then the line intersects the axis of
  //   the rectangle.
  double tMin = -1.0;
  double tMax = 2.0;

  double p[4];
  double q[4];

  double halfWidth  = width / 2.0;
  double halfHeight = height / 2.0;

  double left   = x - halfWidth;
  double right  = x + halfWidth;
  double top    = y - halfWidth;
  double bottom = y + halfWidth;

  // Left
  p[0] = -boundingBox.width;
  q[0] = line->points[0].x - left;

  // Right
  p[1] = boundingBox.width;
  q[1] = right - line->points[0].x;

  // Top
  p[2] = -boundingBox.height;
  q[2] = line->points[0].y - top;

  // Bottom
  p[3] = boundingBox.height;
  q[3] = bottom - line->points[0].y;

  for (int i = 0; i < 4; i++) {
    if (q[i] < 0.0) {
      // Outside rectangle
      return false;
    }
    else if (p[i] < 0.0) {
      // Outside to Inside
      if ((q[i] / p[i]) > tMin) {
        tMin = q[i] / p[i];
      }
    }
    else if (p[i] > 0.0) {
      // Inside to Outside
      if ((q[i] / p[i]) < tMax) {
        tMax = q[i] / p[i];
      }
    }
    else {
      // Parallel lines can be ignored.
    }
  }

  if (tMin > tMax) {
    // Outside
    return false;
  }

  // Line intersects between tMin and tMax

  if (tMin >= 0.0) {
    *t = tMin;
  }
  else if (tMax <= 1.0) {
    *t = tMax;
  }
  else {
    return false;
  }

  return true;
}

bool Badger::Rectangle::contains(Point* point) {
  double halfWidth  = width  / 2.0;
  double halfHeight = height / 2.0;

  bool containsPoint = true;
  containsPoint &= point->x >= x - halfWidth;
  containsPoint &= point->y >= y - halfHeight;
  containsPoint &= point->x <  x + halfWidth;
  containsPoint &= point->y <  y + halfHeight;
  return containsPoint;
}

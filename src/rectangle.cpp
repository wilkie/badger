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
  Point  pMin;
  double tMax = 2.0;
  Point  pMax;

  double p[4];
  double q[4];
  double exactPosition[4];

  double halfWidth  = width / 2.0;
  double halfHeight = height / 2.0;

  double left   = x - halfWidth;
  double right  = x + halfWidth;
  double top    = y - halfWidth;
  double bottom = y + halfWidth;

  // Left
  p[0] = -boundingBox.width;
  q[0] = line->points[0].x - left;
  exactPosition[0] = left;

  // Right
  p[1] = boundingBox.width;
  q[1] = right - line->points[0].x;
  exactPosition[1] = right;

  // Top
  p[2] = -boundingBox.height;
  q[2] = line->points[0].y - top;
  exactPosition[2] = top;

  // Bottom
  p[3] = boundingBox.height;
  q[3] = bottom - line->points[0].y;
  exactPosition[3] = bottom;

  // Special cases (Dare I call them edge cases?)
  // Gliding past the edge
  if (p[0] == 0 && p[1] == 0) {
    if (line->points[0].x == left || line->points[0].x == right) {
      return false;
    }
  }
  else if (p[2] == 0 && p[3] == 0) {
    if (line->points[0].y == top || line->points[0].y == bottom) {
      return false;
    }
  }

  // Unix Vector Magnitudes
  double magnitudeX = line->points[0].x - line->points[1].x;
  double magnitudeY = line->points[0].y - line->points[1].y;

  for (int i = 0; i < 4; i++) {
    if (q[i] < 0.0) {
      // Outside rectangle
      return false;
    }
    else if (p[i] < 0.0) {
      // Outside to Inside
      if ((q[i] / p[i]) > tMin && (q[i] / p[i]) > 0.0) {
        tMin = q[i] / p[i];
        if (i < 2) {
          pMin.x = exactPosition[i];
          pMin.y = line->points[0].y + tMin * magnitudeY;
        }
        else {
          pMin.y = exactPosition[i];
          pMin.x = line->points[0].x + tMin * magnitudeX;
        }
      }
    }
    else if (p[i] > 0.0) {
      // Inside to Outside
      if ((q[i] / p[i]) < tMax && (q[i] / p[i]) < 1.0) {
        tMax = q[i] / p[i];
        if (i < 2) {
          pMax.x = exactPosition[i];
          pMax.y = line->points[0].y + tMax * magnitudeY;
        }
        else {
          pMax.y = exactPosition[i];
          pMax.x = line->points[0].x + tMax * magnitudeX;
        }
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
    line->points[1] = pMin;
  }
  else if (tMax <= 1.0) {
    *t = tMax;
    line->points[1] = pMax;
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

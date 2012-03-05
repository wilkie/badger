#include "badger/collider_agent.h"

#include "badger/point.h"

Badger::ColliderAgent::ColliderAgent(Map* map)
  : _map(map) {
}

bool Badger::ColliderAgent::move(Rectangle* from, Point* to) {
  // For every point px, py in the set of 4 defined by given Rectangle
  Point points[4];
  Point toPoints[4];

  double halfWidth  = from->width  / 2.0;
  double halfHeight = from->height / 2.0;

  points[0].x = from->x - halfWidth;
  points[0].y = from->y - halfHeight;
  toPoints[0].x = to->x - halfWidth;
  toPoints[0].y = to->y - halfHeight;

  points[1].x = from->x + halfWidth;
  points[1].y = from->y - halfHeight;
  toPoints[1].x = to->x + halfWidth;
  toPoints[1].y = to->y - halfHeight;

  points[2].x = from->x + halfWidth;
  points[2].y = from->y + halfHeight;
  toPoints[2].x = to->x + halfWidth;
  toPoints[2].y = to->y + halfHeight;

  points[3].x = from->x - halfWidth;
  points[3].y = from->y + halfHeight;
  toPoints[3].x = to->x - halfWidth;
  toPoints[3].y = to->y + halfHeight;

  Line vectors[4];
  for (int i = 0; i < 4; i++) {
    vectors[i].points[0] = points[i];
    vectors[i].points[1] = toPoints[i];
  }

  // Assume we can move the entire way
  double t = 1.0;

  double magnitudeX = from->x - to->x;
  double magnitudeY = from->y - to->y;

  // determine if there is an intersection with the map
  for (unsigned int x = 0; x < _map->width(); x++) {
    for (unsigned int y = 0; y < _map->height(); y++) {
      Tile* tile = _map->tile(x, y);
      if (tile->passable) {
        continue;
      }

      // Do we intersect?
      Rectangle tileRect;
      tileRect.x = x * 32.0;
      tileRect.y = y * 32.0;

      tileRect.width  = 32.0;
      tileRect.height = 32.0;

      for (int i = 0; i < 4; i++) {
        double tmp_t;

        if (tileRect.intersects(&vectors[i], &tmp_t)) {
          if (tmp_t < t) {
            // New t value is the amount we will walk down the vector

            // We subtract a little so that we always have some padding between us
            //   and the wall
            t = tmp_t - 0.001;
          }
        }
      }
    }
  }

  if (t == 1.0) {
    return true;
  }

  // Get the actual point we should move to
  to->x = from->x + magnitudeX * t;
  to->y = from->y + magnitudeY * t;
  return false;
}

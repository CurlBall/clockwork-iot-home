#include "Point.h"
#include "Logging.h"
#include <Arduino.h>
#include <stdint.h>

Point::Point(int16_t x, int16_t y) : x(x), y(y) {}

Point::~Point() {
  Logging::write("Removing Point");
}

// Returns new instance of Point
Point* Point::getMiddlePoint(Point* p1, Point* p2) {
  int16_t midX = (p1->x + p2->x) / 2;
  int16_t midY = (p1->y + p2->y) / 2;
  return new Point(midX, midY);
}
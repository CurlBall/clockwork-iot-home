#ifndef Point_h
#define Point_h

#include <stdint.h>

class Point {
  public:
    const int16_t x; // Am I breaking the law?
    const int16_t y; // Am I breaking the law?
    Point(int16_t x, int16_t y);
    ~Point();
    static Point* getMiddlePoint(Point* p1, Point* p2);
};

#endif
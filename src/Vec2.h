#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>

struct Vec2 {
    Vec2 (double _x, double _y);
    double x, y;
    Vec2& operator+= (const Vec2& o);
    Vec2& operator-= (const Vec2& o);
    Vec2& operator*= (double a);
    Vec2& operator/= (double a);
    Vec2 operator+ (const Vec2& o) const;
    Vec2 operator- (const Vec2& o) const;
    Vec2 operator* (double a) const;
    Vec2 operator/ (double a) const;
    double dot (const Vec2& o) const;
    double dist2 () const;
    double dist () const;
    double dist2 (const Vec2& v2) const;
    double dist (const Vec2& v2) const;
    Vec2 projection (const Vec2& v2) const;
    Vec2 unit () const;
};
#endif
#include "Vec2.h"

Vec2::Vec2 (double _x, double _y) : x(_x), y(_y) {};

Vec2& Vec2::operator+= (const Vec2& o) {
    x += o.x;
    y += o.y;
    return *this;
}

Vec2& Vec2::operator-= (const Vec2& o) {
    x -= o.x;
    y -= o.y;
    return *this;
}

Vec2& Vec2::operator*= (double a) {
    x *= a;
    y *= a;
    return *this;
}

Vec2& Vec2::operator/= (double a) {
    x /= a;
    y /= a;
    return *this;
}

Vec2 Vec2::operator+ (const Vec2& o) const {
    Vec2 res = *this; return res += o;
}

Vec2 Vec2::operator- (const Vec2& o) const {
    Vec2 res = *this; return res -= o;
}

Vec2 Vec2::operator* (double a) const {
    Vec2 res = *this; return res *= a;
}

Vec2 Vec2::operator/ (double a) const {
    Vec2 res = *this; return res /= a;
}

double Vec2::dot (const Vec2& o) const {
    return x * o.x + y * o.y;
}

double Vec2::dist2 () const {
    return x * x + y * y;
}

double Vec2::dist () const {
    return sqrt(dist2());
}

double Vec2::dist2 (const Vec2& v2) const {
    return (v2 - *this).dist2();
}

double Vec2::dist (const Vec2& v2) const {
    return (v2 - *this).dist();
}

Vec2 Vec2::projection (const Vec2& v2) const {
    return v2 * this->dot(v2) / v2.dist2();
}

Vec2 Vec2::unit () const {
    return *this / dist();
}
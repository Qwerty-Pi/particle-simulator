#ifndef BALL_H_
#define BALL_H_

#include "Vec2.h"

struct Particle {
    Particle (Vec2 _pos, Vec2 _vel, double _mass, double _radius);
    Vec2 hitVelocity (const Particle& b2) const;
    
    Vec2 pos, vel;
    double mass, radius;
};
#endif
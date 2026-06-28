#include "Particle.h"

Particle::Particle (Vec2 _pos, Vec2 _vel, double _mass, double _radius) :
    pos(_pos), vel(_vel), mass(_mass), radius(_radius) {};

Vec2 Particle::hitVelocity (const Particle& other) const {
    double mass_ratio = 2.0 * other.mass / (mass + other.mass);
    Vec2 pos_delta = pos - other.pos;
    Vec2 vel_delta = vel - other.vel;
    Vec2 proj = vel_delta.projection(pos_delta);
    return vel - proj * mass_ratio;
}

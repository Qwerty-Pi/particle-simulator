#include <vector>
#include <algorithm>
#include <cmath>

#include <thread>
#include <atomic>
#include <mutex>

/*******************
 *     HEADER      *
 *******************/

#ifdef ONLINE_JUDGE

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

struct Particle {
    Particle (Vec2 _pos, Vec2 _vel, double _mass, double _radius);
    Vec2 hitVelocity (const Particle& b2) const;
    
    Vec2 pos, vel;
    double mass, radius;
};


// Is particle overlapping with a wall
inline bool is_wall_overlap(Vec2 pos, int width, int height, int radius);
// Is particle colliding with a wall
inline bool is_wall_collision(Vec2 pos, Vec2 vel, int width, int height, int radius);
// Make particle not collide with wall
// PRECONDITION: Can be called with no preconditions
inline void resolve_wall_collision(Vec2 pos, Vec2& vel, int width, int height, int radius);
// Are the particles overlapping
inline bool is_particle_overlap(Vec2 loc1, Vec2 loc2, int radius);
// Are the particles moving closer together
inline bool is_particle_moving_closer(Vec2 loc1, Vec2 vel1, Vec2 loc2, Vec2 vel2);
// Are the particles colliding
inline bool is_particle_collision(Vec2 loc1, Vec2 vel1, Vec2 loc2, Vec2 vel2, int radius);
// Make particles not collide with each other
// PRECONDITION: Must only be called if particles are overlapping
inline void resolve_particle_collision(Vec2 loc1, Vec2& vel1, Vec2 loc2, Vec2& vel2);
// Get the total energy of a group of particles
inline double getEnergy(std::vector<Particle>& particles);
// Get the total momentum of a group of particles
inline Vec2 getMomentum(std::vector<Particle>& particles);

#else

#include "collision.h"

#endif

/*******************
 * IMPLEMENTATIONS *
 *******************/
double bbox_width, bbox_height;

void init_frame(double width, double height, double radius) {
    bbox_width = width, bbox_height = height;
}

std::vector<Particle> next_frame(std::vector<Particle> particles, double dt) {
    for (Particle& p : particles) {
        p.pos += p.vel * dt;
    }

    int num_collisions = 1;

    while (num_collisions > 0) {
        num_collisions = 0; 

        auto handleParticleCollision = [&] (Particle *p1, Particle *p2) {
            if (is_particle_overlap(p1->pos, p2->pos, p1->radius + p2->radius)
                && is_particle_moving_closer(p1->pos, p1->vel, p2->pos, p2->vel)) {
                resolve_particle_collision(p1->pos, p1->vel, p2->pos, p2->vel);
                ++num_collisions;
            }
        };

        for (Particle& p : particles) {
            Vec2 old_pos = p.pos;
            resolve_wall_collision(p.pos, p.vel, bbox_width, bbox_height, p.radius);
            
            if (p.pos.x != old_pos.x || p.pos.y != old_pos.y) {
                ++num_collisions;
            }
        }

        int num_particles = (int) particles.size();
        for (int i = 0; i < num_particles; i++) {
            for (int j = i + 1; j < num_particles; j++) {
                handleParticleCollision(&particles[i], &particles[j]);
            }
        }
    }
    return particles;
}

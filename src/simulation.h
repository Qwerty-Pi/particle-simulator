#include <vector>
#include "Particle.h"

void init_frame(double width, double height, double radius);
std::vector<Particle> next_frame(std::vector<Particle> particles, double dt);

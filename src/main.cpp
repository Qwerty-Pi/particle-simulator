#include "raylib.h"

#include <vector>
#include <string>
#include <random>
#include <deque>
#include "simulation.h"
#include "collision.h"

// Generates a vector of non-overlapping particles within a specified bounding box
std::vector<Particle> generateRandomParticles(int target_count, double bbox_width, double bbox_height, double radius, double speed_limit) {
    std::vector<Particle> particles;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Configure your ranges here
    std::uniform_real_distribution<double> speed_dist(-speed_limit, speed_limit);

    int attempts = 0;
    int max_attempts = 10000; // Prevents infinite loops if space runs out

    while (particles.size() < target_count && attempts < max_attempts) {
        attempts++;
        
        // Prevent particles from spawning partially outside the boundary walls
        std::uniform_real_distribution<double> pos_x_dist(radius, bbox_width - radius);
        std::uniform_real_distribution<double> pos_y_dist(radius, bbox_height - radius);
        
        double x = pos_x_dist(gen);
        double y = pos_y_dist(gen);
        
        bool overlapping = false;
        for (const auto& existing_ball : particles) {
            double dx = x - existing_ball.pos.x;
            double dy = y - existing_ball.pos.y;
            double distance_squared = (dx * dx) + (dy * dy);
            
            double min_distance = radius + existing_ball.radius;
            double min_distance_squared = min_distance * min_distance;
            
            if (distance_squared < min_distance_squared) {
                overlapping = true;
                break; // Found a collision, discard this attempt
            }
        }
        
        if (!overlapping) {
            double vx = speed_dist(gen);
            double vy = speed_dist(gen);
            double mass = (radius * radius) * 0.1f; // Mass proportional to size
            
            particles.push_back(Particle(Vec2(x, y), Vec2(vx, vy), mass, radius));
        }
    }
    
    return particles;
}

int main () {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	double window_width = 800;
	double window_height = 600;
	double bbox_padding = 50;
	double bbox_width = window_width - bbox_padding * 2;
	double bbox_height = window_height - bbox_padding * 2;

	InitWindow(window_width, window_height, "Particle Simulator");

	// std::vector<Particle> particles {
	// 	Particle(Vec2(100, 100), Vec2(200, 80), 50, 50),
	// 	Particle(Vec2(300, 200), Vec2(-100, -20), 20, 50),
	// 	Particle(Vec2(20, 20), Vec2(100, 100), 100, 30)
	// };

	int num_particles = 1500;
	double particle_radius = 4.0f;
	double speed_limit = 50.0f;
	std::vector<Particle> particles = generateRandomParticles(num_particles, bbox_width, bbox_height, particle_radius, speed_limit);
	init_frame(bbox_width, bbox_height, particle_radius);
	// SetTargetFPS(60);

	std::deque<double> frame_times;

	while (!WindowShouldClose()) {
		double dt = GetFrameTime();
		frame_times.push_back(dt);
		if (frame_times.size() > 60) {
			frame_times.pop_front();
		}
		double average_frame_time = accumulate(frame_times.begin(), frame_times.end(), 0.0) / frame_times.size();

		particles = next_frame(particles, dt);
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(("FPS: " + std::to_string(1.0f / average_frame_time)).c_str(), 5, 5, 20, WHITE);
		DrawText(("No. of Particles: " + std::to_string(particles.size())).c_str(), 205, 5, 20, WHITE);

		DrawRectangle(bbox_padding, bbox_padding, bbox_width, bbox_height, VIOLET);
		double border_width = 2;
		for (const Particle ball : particles) {
			DrawCircle(bbox_padding + ball.pos.x, bbox_padding + ball.pos.y, ball.radius, WHITE);
			DrawCircle(bbox_padding + ball.pos.x, bbox_padding + ball.pos.y, ball.radius - border_width / 2, BLUE);
		}
		DrawText(("Energy: " + std::to_string(getEnergy(particles))).c_str(), 455, 5, 20, WHITE);
        EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

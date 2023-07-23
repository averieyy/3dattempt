#include <list>
#include <vector>
#include "terrain.cpp"

double camera_x = 8;
double camera_y = 0;
double camera_z = 8;

bool player_on_ground = true;

double camera_rot_x = 0; // Spinnies
double camera_rot_y = 0; // Uppies
double camera_rot_z = 0; // Head spinnies

int originx = 0;
int originy = 0;

int focal_length = 3;

// Object lists
std::list<std::vector<double>> vertecies;
std::list<std::vector<int>> faces[] = {{}};
std::vector<terrain_chunk> chunks;
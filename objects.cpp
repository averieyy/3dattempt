#include <list>
#include <vector>

double camera_x = 0;
double camera_y = 0;
double camera_z = -5;

double camera_rot_x = 0; // Spinnies
double camera_rot_y = 0; // Uppies
double camera_rot_z = 0; // Head spinnies

int originx = 0;
int originy = 0;

int focal_length = 3;

// Object lists
std::list<std::vector<double>> vertecies = {{1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1},{1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1}};
std::list<std::vector<int>> lines = {{0,1},{2,3},{4,5},{6,7},{0,2},{0,4},{1,3},{1,5},{2,6},{3,7},{4,6}, {5,7}};
std::list<std::vector<int>> faces[] = {{}};
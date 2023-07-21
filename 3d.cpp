#include <vector>
#include <cmath>
#include "objects.cpp"

std::vector<double> coord_from_vertex(std::vector<double> vertex) {
    double x = vertex[0] - camera_x;
    double y = vertex[1] - camera_y;
    double z = vertex[2] - camera_z;

    double dx = cos(camera_rot_y)*(sin(camera_rot_z)*y + cos(camera_rot_z)*x) - sin(camera_rot_y) * z;
    double dy = sin(camera_rot_x)*(cos(camera_rot_y)*z + sin(camera_rot_y)*(sin(camera_rot_z)*y + cos(camera_rot_z)*x)) + cos(camera_rot_x) * (cos(camera_rot_z)*y - sin(camera_rot_z)*x);
    double dz = cos(camera_rot_x)*(cos(camera_rot_y)*z + sin(camera_rot_y)*(sin(camera_rot_z)*y + cos(camera_rot_z)*x)) - sin(camera_rot_x) * (cos(camera_rot_z)*y - sin(camera_rot_z)*x);
    
    if (dz < 0) return std::vector<double> {};
    // double dx = cos(camera_rot_y)*(sin(camera_rot_z)*pp_vy+cos(camera_rot_z)*pp_vx) - sin(camera_rot_y)*pp_vz;
    // double dy = sin(camera_rot_x)*(cos(camera_rot_y)*pp_vz+sin(camera_rot_y)*(sin(camera_rot_z)*pp_vy+cos(camera_rot_z)*pp_vx)) + cos(camera_rot_x)*(cos(camera_rot_z)*pp_vy+sin(camera_rot_z)*pp_vx);
    // double dz = cos(camera_rot_x)*(cos(camera_rot_y)*pp_vz+sin(camera_rot_y)*(sin(camera_rot_z)*pp_vy+cos(camera_rot_z)*pp_vx)) - sin(camera_rot_x)*(cos(camera_rot_z)*pp_vy+sin(camera_rot_z)*pp_vx);

    // // Project vertex
    // double px = dx * (focal_length / dz);
    // double py = dy * (focal_length / dz);

    double px = dx * (focal_length / dz)*100 + originx;
    double py = dy * (focal_length / dz)*100 + originy;

    return std::vector<double> {px, py}; // return projected vertex
}
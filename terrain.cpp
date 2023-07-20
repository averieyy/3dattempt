#include "PerlinNoise.hpp"
#include <list>
#include <vector>

#define CHUNK_SIZE 16

struct terrain_chunk {
    double matrix[CHUNK_SIZE][CHUNK_SIZE];
    int x = 0;
    int y = 0;
};

terrain_chunk create_chunk (int x, int y) {
    terrain_chunk c;
    c.x = x;
    c.y = y;
    siv::PerlinNoise::seed_type seed = 200000u;
    siv::PerlinNoise perlin{ seed }; 
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int ii = 0; ii < CHUNK_SIZE; ii++) {
			const double noise = (perlin.octave2D_01(((i + x * CHUNK_SIZE) * 0.01), ((ii + y * CHUNK_SIZE) * 0.01), 4) + 
            perlin.octave2D_01(((i + x * CHUNK_SIZE) * 0.01), ((ii + y * CHUNK_SIZE) * 0.01), 10) + 
            perlin.octave2D_01(((i + x * CHUNK_SIZE) * 0.01), ((ii + y * CHUNK_SIZE) * 0.01), 20));
            c.matrix[i][ii] = noise;
        }
    }
    return c;
}

std::list<std::vector<double>> chunk_to_vertecies(terrain_chunk c) {
    std::list<std::vector<double>> vertecies;
    for (double i = 0; i < CHUNK_SIZE; i ++) {
        for (double ii = 0; ii < CHUNK_SIZE; ii++) {
            vertecies.push_back(std::vector{c.x*CHUNK_SIZE + i, c.matrix[(int)i][(int)ii]*10, c.y*CHUNK_SIZE + ii});
        }
    }
    return vertecies;
}
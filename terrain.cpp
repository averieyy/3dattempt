#include "PerlinNoise.hpp"
#include <list>
#include <vector>
#include <random>

#define CHUNK_SIZE 16

struct terrain_chunk {
    double matrix[CHUNK_SIZE][CHUNK_SIZE];
    int x = 0;
    int y = 0;
    int type = 0;
};

double get_perlin_at (double x, double y) {
    siv::PerlinNoise::seed_type seed = 200000u;
    siv::PerlinNoise perlin { seed };
    const double noise = (perlin.octave2D_01((x * 0.01), (y * 0.01), 4) + 
                          perlin.octave2D_01((x * 0.01), (y * 0.01), 10) + 
                          perlin.octave2D_01((x * 0.01), (y * 0.01), 20));
    return noise;
}

terrain_chunk create_chunk (int x, int y) {
    terrain_chunk c;
    c.x = x;
    c.y = y;
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int ii = 0; ii < CHUNK_SIZE; ii++) {
            c.matrix[i][ii] = get_perlin_at((i + x * CHUNK_SIZE), (ii + y * CHUNK_SIZE));
        }
    }
    return c;
}

std::list<std::vector<double>> chunk_to_vertecies(terrain_chunk c) {
    std::list<std::vector<double>> vertecies;
    for (double i = 0; i < CHUNK_SIZE; i ++) {
        for (double ii = 0; ii < CHUNK_SIZE; ii++) {
            vertecies.push_back(std::vector<double>{c.x*CHUNK_SIZE + i, c.matrix[(int)i][(int)ii]*10, c.y*CHUNK_SIZE + ii});
        }
    }
    return vertecies;
}

std::vector<terrain_chunk> create_landscape (int sx, int sy, int size) { // start x, start y (corners), size (ex. 5x5 chunks)
    std::vector<terrain_chunk> landscape;
    
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            landscape.push_back(create_chunk(sx + x, sy + y));
        }
    }

    landscape[size*size-1].type = 1;

    int x = -1;
    int y = -1;
    while ((x == -1 && y == -1) || (x == 0 && y == 0) || landscape[y*size+x].type != 0) {
        x = ((double)rand()/(double)RAND_MAX)*size;
        y = ((double)rand()/(double)RAND_MAX)*size;
    }

    landscape[y*size+x].type = 2;

    return landscape;
}
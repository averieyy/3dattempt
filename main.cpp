#include "SDL.h"
#include <iostream>
#include "3d.cpp"
#include <math.h>

// Some definitions
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

#define FPS 60

bool should_clip (std::vector<int> line, std::vector<double> vertex1, std::vector<double> vertex2, int wh, int ww) {
    if (vertex1.size() == 0 || vertex2.size() == 0) return true; // Checks if vector is empty (vertex is not visible)
    if (vertex1[0] > -1000 && vertex1[0] <= ww+1000 && vertex1[1] > -1000 && vertex1[1] <= wh+1000 &&
        vertex2[0] > -1000 && vertex2[0] <= ww+1000 && vertex2[1] > -1000 && vertex2[1] <= wh+1000) // Do not render if the line is going too far off screen (Crash pervention)
        return false;
    return true;
}

int get_chunk_type (double x, double y) {
    for (auto c : chunks) {
        if (x <= c.x*CHUNK_SIZE + CHUNK_SIZE && x > c.x * CHUNK_SIZE) {
            if (y <= c.y*CHUNK_SIZE + CHUNK_SIZE && y > c.y * CHUNK_SIZE) {
                
                return c.type;
            }
        }
    }
    return 0;
}

int main () {
    // controls
    bool Left = false;
    bool Down = false;
    bool Right = false;
    bool Up = false;
    bool W = false;
    bool A = false;
    bool S = false;
    bool D = false;

    // Movement velocity
    double x_velocity = 0;
    double y_velocity = 0.025;
    double z_velocity = 0;

    double speed_modifier = 1;

    double x_rot_v = 0;
    double y_rot_v = 0;

    //window
    int window_w = WINDOW_WIDTH;
    int window_h = WINDOW_HEIGHT;

    // Init SDL and the window
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("lorem ipsum", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_SHOWN);

    // I will probably need to change these later
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 1, 0);

    originx = window_w / 2;
    originy = window_h / 2;

    SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    // Initialize landscape
    chunks = create_landscape(0,0,5);
    bool can_proceed = false;

    SDL_Event ev;

    double idealdelta = 1000000000 / FPS;
    
    bool running = true;
    long now = SDL_GetPerformanceCounter();
    long last = 0;
    double delta = 0;

    while (running) {
        last = now;
        now = SDL_GetPerformanceCounter();

        if (delta < idealdelta / 10)
            SDL_Delay((idealdelta - delta) / 1000000);

        delta += (double) (now-last);

        if (delta >= idealdelta) {

            delta = delta - idealdelta;

            // Events
            while ( SDL_PollEvent( &ev ) != 0) {
                switch (ev.type) {
                    // Quit and terminating
                    case SDL_QUIT:
                        running = false;
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 0;
                        break;
                    case SDL_APP_TERMINATING:
                        running = false;
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 0;
                    // Keyevents
                    case SDL_KEYDOWN:
                        switch(ev.key.keysym.sym){
                            case SDLK_LEFT:
                                Left = true;
                                break;
                            case SDLK_DOWN:
                                Down = true;
                                break;
                            case SDLK_RIGHT:
                                Right = true;
                                break;
                            case SDLK_UP:
                                Up = true;
                                break;
                            case SDLK_w:
                                W = true;
                                break;
                            case SDLK_a:
                                A = true;
                                break;
                            case SDLK_s:
                                S = true;
                                break;
                            case SDLK_d:
                                D = true;
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        switch(ev.key.keysym.sym){
                            case SDLK_LEFT:
                                Left = false;
                                break;
                            case SDLK_DOWN:
                                Down = false;
                                break;
                            case SDLK_RIGHT:
                                Right = false;
                                break;
                            case SDLK_UP:
                                Up = false;
                                break;
                            case SDLK_w:
                                W = false;
                                break;
                            case SDLK_a:
                                A = false;
                                break;
                            case SDLK_s:
                                S = false;
                                break;
                            case SDLK_d:
                                D = false;
                                break;
                        }
                        break;
                    // Resizing and such
                    case SDL_WINDOWEVENT:
                        if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
                            window_w = ev.window.data1;
                            window_h = ev.window.data2;
                            originx = window_w / 2;
                            originy = window_h / 2;
                        }
                        break;
                }
            }

            // Move camera

            // if (Left) camera_x -= 10.0/FPS;
            // if (Right) camera_x += 10.0/FPS;
            if (Left && (y_rot_v <= 4.0/FPS || y_rot_v >= -4.0/FPS)) {
                y_rot_v -= 1.0/FPS/5;
            }
            if (Right && (y_rot_v <= 4.0/FPS || y_rot_v >= -4.0/FPS)) {
                y_rot_v += 1.0/FPS/5;
            }
            if (Up && abs(x_velocity) < 2 && abs(z_velocity) < 2) {
                x_velocity += sin(camera_rot_y) / FPS * speed_modifier;
                z_velocity += cos(camera_rot_y) / FPS * speed_modifier;
            }
            if (Down && abs(x_velocity) < 2 && abs(z_velocity) < 2) {
                x_velocity -= sin(camera_rot_y) / FPS * speed_modifier;
                z_velocity -= cos(camera_rot_y) / FPS * speed_modifier;
            }

            if (!Down && !Up && (Right || Left)) {
                // Drift
                if (Left) {

                }
            }

            camera_x += x_velocity;
            camera_z += z_velocity;

            camera_rot_y += y_rot_v;

            x_velocity *= 0.97;
            z_velocity *= 0.97;

            y_rot_v *= 0.95;
            if (!Left && !Right || (!Up && !Down)) y_rot_v *= 0.9;

            // OLD ROTATION
            // if (W && camera_rot_x <= 1.5) camera_rot_x += 1.0/FPS;
            // if (A) camera_rot_y -= 1.0/FPS;
            // if (S && camera_rot_x > -1.5) camera_rot_x -= 1.0/FPS;
            // if (D) camera_rot_y += 1.0/FPS;

            // Gravity & staying on the ground
            double ground_height = get_perlin_at(camera_x, camera_z) * 10 - 2;
            if (player_on_ground &&
                camera_y >= ground_height) {
                camera_y = ground_height;
                speed_modifier = 0.75;
            }
            else {
                speed_modifier = 1;
                if (player_on_ground) y_velocity = 0.015;
                player_on_ground = false;
                if (camera_y < ground_height) {
                    if (y_velocity <= 0.75)
                        y_velocity *= 1.12;
                    camera_y += y_velocity;
                }
                else {
                    camera_y = ground_height;
                    player_on_ground = true;
                }
            }

            // Add points & start next level
            if (player_on_ground) {
                switch (get_chunk_type(camera_x, camera_z)) {
                    case 2:
                        can_proceed = true;
                        for (int i = 0; i < chunks.size(); ++i) {
                            if (chunks[i].type == 2) chunks[i].type = 0;
                        }
                        break;
                    case 1:
                        if (can_proceed) {
                            can_proceed = false;
                            chunks = create_landscape(chunks[chunks.size()-1].x, chunks[chunks.size()-1].y, 5);
                        }
                }
            }

            // Clear Screen
            SDL_SetRenderDrawColor(renderer, 0,0,0,255);

            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255,255,255, 255);

            // Render landscape
            for (auto j : chunks) {

                switch (j.type) {
                    case 0:
                        SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
                        break;
                    case 1:
                        SDL_SetRenderDrawColor(renderer, 0,0,255, 255);
                        break;
                    case 2:
                        SDL_SetRenderDrawColor(renderer, 0,255,0, 255);
                        break;
                }
                
                // PROJECT VERTECIES
                std::vector<std::vector<double>> p_ver = {};
                
                for (auto i : chunk_to_vertecies(j)) {
                    std::vector<double> coord = coord_from_vertex(i);
                    if (coord.size() == 0) {
                        p_ver.push_back({});
                        continue;
                    } // Handle non-visible vertecies
                    p_ver.push_back({coord[0], coord[1]});
                    SDL_RenderDrawPoint(renderer, coord[0], coord[1]); // Render vertex
                }
                // Generate lines between vertecies
                std::list<std::vector<int>> lines;

                for (int x = 0; x < CHUNK_SIZE; ++x) {
                    for (int y = 0; y < CHUNK_SIZE; ++y) {
                        if (x != 15) {
                            lines.push_back(std::vector<int>{y*CHUNK_SIZE+x,y*CHUNK_SIZE+x+1});
                        }
                        if (y != 15) {
                            lines.push_back(std::vector<int>{y*CHUNK_SIZE+x,(y+1)*CHUNK_SIZE+x});
                        }
                        if (y != 15 && x != 15) {
                            lines.push_back(std::vector<int>{y*CHUNK_SIZE+x,(y+1)*CHUNK_SIZE+x+1});
                        }
                    }
                }

                // Render lines
                for (auto i : lines) {
                    if (!should_clip(i, p_ver[i[0]], p_ver[i[1]], window_w, window_h))
                        SDL_RenderDrawLine(renderer, p_ver[i[0]][0], p_ver[i[0]][1], p_ver[i[1]][0], p_ver[i[1]][1]);
                }
            }

            // Render (Show rendered)
            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}

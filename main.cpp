#include "SDL.h"
#include <iostream>
#include "3d.cpp"

// Some definitions
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

#define FPS 60

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

    //window
    int window_w = WINDOW_WIDTH;
    int window_h = WINDOW_HEIGHT;

    // Init SDL and the window
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("lorem ipsum", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_MAXIMIZED);

    // I will probably need to change these later
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 1, 0);

    originx = window_w / 2;
    originy = window_h / 2;

    SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    // Initialize landscape
    for (int i = 0; i < 5; i++) {
        for (int ii = 0; ii < 5; ++ii) {
            chunks.push_back(create_chunk(i,ii));
        }
    }

    double idealdelta = 1000000000 / FPS;

    SDL_Event ev;

    bool running = true;
    long now = SDL_GetPerformanceCounter();
    long last = 0;
    double delta = 0;
    while (running) {
        last = now;
        now = SDL_GetPerformanceCounter();

        delta += (double) (now-last);

        if (delta >= idealdelta) {

            delta = delta - idealdelta;

            while ( SDL_PollEvent( &ev ) != 0) {
                switch (ev.type) {
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

            if (Left) camera_x -= 10.0/FPS;
            if (Right) camera_x += 10.0/FPS;
            if (Up) camera_z += 10.0/FPS;
            if (Down) camera_z -= 10.0/FPS;
            if (W && camera_rot_x <= 1.5) camera_rot_x += 1.0/FPS;
            if (A) camera_rot_y -= 1.0/FPS;
            if (S && camera_rot_x > -1.5) camera_rot_x -= 1.0/FPS;
            if (D) camera_rot_y += 1.0/FPS;

            SDL_SetRenderDrawColor(renderer, 0,0,0,255);

            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255,255,255, 255);


            for (auto j : chunks) {
                
                std::vector<std::vector<double>> p_ver = {};
                
                for (auto i : chunk_to_vertecies(j)) {
                    std::vector<double> coord = coord_from_vertex(i);
                    p_ver.push_back({coord[0], coord[1]});
                    SDL_RenderDrawPoint(renderer, coord[0], coord[1]);
                }

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

                for (auto i : lines) {
                    if (p_ver[i[0]][0] > -1000 && p_ver[i[0]][0] <= window_w+1000 && p_ver[i[0]][1] > -1000 && p_ver[i[0]][1] <= window_h+1000 &&
                        p_ver[i[1]][0] > -1000 && p_ver[i[1]][0] <= window_w+1000 && p_ver[i[1]][1] > -1000 && p_ver[i[1]][1] <= window_h+1000)
                        SDL_RenderDrawLine(renderer, p_ver[i[0]][0], p_ver[i[0]][1], p_ver[i[1]][0], p_ver[i[1]][1]);
                }
            }

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}

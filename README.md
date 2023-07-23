# an attempt

This is an attempt at creating a 3D game / renderer from scratch

Continue at your own risk



## TODO
- [x] Basic projection
- [ ] Game dev (driving sim)
    - [x] Procedural generation
        - [x] Terrain generation (perlin noise)
        - [x] Expandable map
    - [x] Gravity (Landscape collision)
    - [x] Driving (movement)
    - [x] Goal & Point system
    - 
- Bugs
    - [x] Movement doesn't change based on rotation
        - [x] Also uses a lot of the cpu
    - [x] Vertices behind the camera still render
        - [x] Lines occationally render where they should'nt
    - [ ] Game often uses 100% CPU
    - [ ] Game freezes while loading next landscape



## Credits

- [SDL]("https://www.libsdl.org") - libSDL org
- [Perlin Noise]("https://github.com/Reputeless/PerlinNoise") - github/Reputeless
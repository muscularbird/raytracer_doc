#ifndef GAME_HPP
    #define GAME_HPP

    #include "raylib.h"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void update();
    void draw();

    Camera3D camera3D;
};

#endif

#ifndef GAME_HPP
    #define GAME_HPP

    #include "raylib.h"

    #include "../include/logger/Logger.hpp"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void update();
    void draw();

    Camera3D camera3D;
    Vector3 cameraDirection;  // Direction dans laquelle la caméra regarde
    float cameraSpeed = 0.2f;
    float yaw = 0.0f;   // rotation horizontale (gauche/droite)
    float pitch = 0.0f; // rotation verticale (haut/bas)


    Model paper_plane;
    Model a340_model;
    Texture2D planeTexture;
};

#endif

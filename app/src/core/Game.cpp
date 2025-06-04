#include "core/Game.hpp"
#include "graphics/SquareComponent.hpp"

Game::Game() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Zappy GUI");
    SetTargetFPS(60);

    //cam init
    camera3D.position = { 4.0f, 4.0f, 4.0f };   // Position de la caméra dans le monde
    camera3D.target = { 0.0f, 0.0f, 0.0f };     // Où elle regarde
    camera3D.up = { 0.0f, 1.0f, 0.0f };         // Axe vertical
    camera3D.fovy = 45.0f;                      // Champ de vision
    camera3D.projection = CAMERA_PERSPECTIVE;  // Perspective classique

}

Game::~Game() {
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}

void Game::update() {
    if (IsKeyDown(KEY_W)) camera3D.position.z -= 0.1f;
    if (IsKeyDown(KEY_S)) camera3D.position.z += 0.1f;
    if (IsKeyDown(KEY_A)) camera3D.position.x -= 0.1f;
    if (IsKeyDown(KEY_D)) camera3D.position.x += 0.1f;
    if (IsKeyDown(KEY_SPACE)) camera3D.position.y += 0.1f;
    if (IsKeyDown(KEY_LEFT_SHIFT)) camera3D.position.y -= 0.1f;
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(camera3D);

// Dessine un cube à l'origine
    DrawCube({0.0f, 0.5f, 0.0f}, 1.0f, 1.0f, 1.0f, RED);
    DrawGrid(10, 1.0f); // Une grille au sol

    EndMode3D();

    DrawText("Zappy GUI 3D View", 10, 10, 20, DARKGRAY);
    EndDrawing();

}


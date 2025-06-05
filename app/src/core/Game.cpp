#include "core/Game.hpp"
#include "graphics/SquareComponent.hpp"
#include "raymath.h"

Game::Game() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Zappy GUI");
    SetTargetFPS(60);

    // Caméra initiale
    camera3D.position = { 0.0f, 2.0f, 5.0f };   // Position de départ
    cameraDirection = { 0.0f, 0.0f, -1.0f };    // Direction initiale (vers -Z)
    camera3D.up = { 0.0f, 1.0f, 0.0f };
    camera3D.fovy = 45.0f;
    camera3D.projection = CAMERA_PERSPECTIVE;
    yaw = PI; // oriente la caméra vers -Z (origine)

    // Chargement modèles
    paper_plane = LoadModel("./assets/paper_plane_asset.obj");
    if (paper_plane.meshCount == 0) {
        Logger::getInstance().log("Failed to load model!", LogLevel::INFO);
    }
    if (!FileExists("./assets/paper_plane_asset.obj")) {
        Logger::getInstance().log("Model file not found at given path!", LogLevel::INFO);
    }
    for (int i = 0; i < paper_plane.materialCount; i++) {
        paper_plane.materials[i].maps[MATERIAL_MAP_DIFFUSE].color = RED;
    }

    a340_model = LoadModel("./assets/a340/a340.obj");
    if (a340_model.meshCount == 0) {
        Logger::getInstance().log("Failed to load model!", LogLevel::INFO);
    }
    if (!FileExists("./assets/a340/a340.obj")) {
        Logger::getInstance().log("Model file not found at given path!", LogLevel::INFO);
    }
}

Game::~Game() {
    UnloadModel(paper_plane);
    UnloadModel(a340_model);
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}

void Game::update() {
    float moveSpeed = 0.2f;
    float rotateSpeed = 0.02f;

    // Contrôles de rotation caméra (Q/D/Z/S inversés)
    if (IsKeyDown(KEY_W)) pitch += rotateSpeed;  // Z physique → regarde vers le bas
    if (IsKeyDown(KEY_S)) pitch -= rotateSpeed;  // S physique → regarde vers le haut
    if (IsKeyDown(KEY_A)) yaw   += rotateSpeed;  // Q physique → pivote à droite
    if (IsKeyDown(KEY_D)) yaw   -= rotateSpeed;  // D physique → pivote à gauche

    // Clamp pitch pour éviter les retournements
    if (pitch > PI / 2.0f) pitch = PI / 2.0f;
    if (pitch < -PI / 2.0f) pitch = -PI / 2.0f;

    // Mise à jour de la direction de la caméra
    cameraDirection.x = cosf(pitch) * sinf(yaw);
    cameraDirection.y = sinf(pitch);
    cameraDirection.z = cosf(pitch) * cosf(yaw);

    // Déplacement latéral (← / →)
    Vector3 right = Vector3Normalize(Vector3CrossProduct(cameraDirection, camera3D.up));
    if (IsKeyDown(KEY_RIGHT)) camera3D.position = Vector3Add(camera3D.position, Vector3Scale(right, moveSpeed));
    if (IsKeyDown(KEY_LEFT))  camera3D.position = Vector3Subtract(camera3D.position, Vector3Scale(right, moveSpeed));

    // Déplacement vertical (↑ / ↓)
    if (IsKeyDown(KEY_UP))    camera3D.position.y += moveSpeed;
    if (IsKeyDown(KEY_DOWN))  camera3D.position.y -= moveSpeed;

    // Avancer / Reculer avec Espace / Shift
    if (IsKeyDown(KEY_SPACE)) {
        camera3D.position = Vector3Add(camera3D.position, Vector3Scale(cameraDirection, moveSpeed));
    }
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        camera3D.position = Vector3Subtract(camera3D.position, Vector3Scale(cameraDirection, moveSpeed));
    }

    // Mise à jour de la cible
    camera3D.target = Vector3Add(camera3D.position, cameraDirection);
}




void Game::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(camera3D);

    DrawGrid(10, 1.0f);
    DrawModel(paper_plane, {0.0f, 0.0f, 0.0f}, 0.001f, WHITE);
    DrawModel(a340_model, {0.0f, 0.0f, 0.0f}, 0.001f, WHITE);

    EndMode3D();

    DrawText("Zappy GUI 3D View - Flèches pour se déplacer", 10, 10, 20, DARKGRAY);
    EndDrawing();
}

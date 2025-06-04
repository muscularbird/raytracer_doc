#ifndef SQUARE_COMPONENT_HPP
    #define SQUARE_COMPONENT_HPP

    #include "raylib.h"

class SquareComponent {
public:
    SquareComponent(float x, float y, float width, float height, Color color);

    void draw() const;

    // Accesseurs / Mutateurs si besoin
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setColor(Color color);

private:
    Vector2 position;
    Vector2 size;
    Color color;
};

#endif

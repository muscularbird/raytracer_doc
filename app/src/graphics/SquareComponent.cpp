#include "../../include/graphics/SquareComponent.hpp"

SquareComponent::SquareComponent(float x, float y, float width, float height, Color color)
        : position{ x, y }, size{ width, height }, color(color) {}

void SquareComponent::draw() const {
    DrawRectangleV(position, size, color);
}

void SquareComponent::setPosition(float x, float y) {
    position = { x, y };
}

void SquareComponent::setSize(float width, float height) {
    size = { width, height };
}

void SquareComponent::setColor(Color c) {
    color = c;
}

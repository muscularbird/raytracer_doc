#include "../include/CircleShape.hpp"

namespace Plazza::Components {

    CircleShape::CircleShape(float radius) {
        _shape.setRadius(radius);
        _shape.setFillColor(sf::Color::White);
    }

    void CircleShape::setPosition(sf::Vector2f position) {
        _shape.setPosition(position);
    }

    void CircleShape::draw(sf::RenderWindow& window) {
        window.draw(_shape);
    }

}

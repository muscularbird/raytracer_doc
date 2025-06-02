#include "../include/RectangleShape.hpp"

namespace Plazza::Components {

    RectangleComponent::RectangleComponent(sf::Vector2f size) {
        _shape.setSize(size);
        _shape.setFillColor(sf::Color::White);
    }

    void RectangleComponent::setPosition(sf::Vector2f position) {
        _shape.setPosition(position);
    }

    void RectangleComponent::draw(sf::RenderWindow& window) {
        window.draw(_shape);
    }

}

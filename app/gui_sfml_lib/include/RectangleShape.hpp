#pragma once
#include <SFML/Graphics.hpp>

namespace Plazza::Components {

    class RectangleComponent {
    public:
        RectangleComponent(sf::Vector2f size);

        void setPosition(sf::Vector2f position);
        void draw(sf::RenderWindow& window);

    private:
        sf::RectangleShape _shape;
    };

}

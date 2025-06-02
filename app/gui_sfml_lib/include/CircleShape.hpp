#pragma once
#include <SFML/Graphics.hpp>

namespace Plazza::Components {

    class CircleShape {
    public:
        CircleShape(float radius);

        void setPosition(sf::Vector2f position);
        void draw(sf::RenderWindow& window);

    private:
        sf::CircleShape _shape;
    };

}

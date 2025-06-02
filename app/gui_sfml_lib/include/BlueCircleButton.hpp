#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

namespace Plazza::Components {
    class BlueCircleButton {
    public:
        BlueCircleButton(const std::string& text, float radius);

        void setPosition(sf::Vector2f pos);
        void update(const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        bool isClicked(const sf::RenderWindow& window);

    private:
        sf::Font _font;
        sf::CircleShape _shape;
        sf::Text _text;
        sf::Color _normalColor;
        sf::Color _hoverColor;
    };
}

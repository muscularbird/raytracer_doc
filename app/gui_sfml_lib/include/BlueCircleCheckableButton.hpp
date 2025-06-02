#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

namespace Plazza::Components {
    class BlueCircleCheckableButton {
    public:
        BlueCircleCheckableButton(const std::string& text, float radius);

        void setPosition(sf::Vector2f pos);
        void update(const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        bool isClicked(const sf::RenderWindow& window);
        void handleClick(const sf::RenderWindow& window);
        bool isActive() const;

    private:
        sf::Font _font;
        sf::CircleShape _shape;
        sf::Text _text;
        sf::Text _cross;
        sf::Color _normalColor;
        sf::Color _hoverColor;
        bool _active = false;
    };
}


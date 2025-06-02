#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Plazza::Components {

    class BlueButton {
    public:
        BlueButton(const std::string& text, sf::Vector2f size);

        void setPosition(sf::Vector2f pos);
        void update(const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        bool isClicked(const sf::RenderWindow& window);

    private:
        sf::RectangleShape _shape;
        sf::Text _text;
        sf::Font _font;

        sf::Color _normalColor;
        sf::Color _hoverColor;
    };

}

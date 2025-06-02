#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Plazza::Components {

    class TextInputComponent {
    public:
        TextInputComponent(const std::string& placeholder);

        void setPosition(float startX, float endX, float startY, float endY);
        void handleEvent(const sf::Event& event);
        void draw(sf::RenderWindow& window);
        std::string getText() const;
        void clear();
        void setText(const std::string& content);

    private:
        sf::Font _font;
        sf::Text _displayText;
        sf::Text _placeholderText;
        sf::RectangleShape _box;

        std::string _inputText;
        float _startX, _endX, _y;
        float _lineHeight;
        float _endY;

        void wrapText();
    };

}

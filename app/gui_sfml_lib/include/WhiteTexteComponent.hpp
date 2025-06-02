#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Plazza::Components {

    class WhiteTexteComponent {
    public:
        WhiteTexteComponent(const std::string& content);

        void setText(const std::string& content);
        void setPosition(float startX, float endX, float startY, float endY);
        void draw(sf::RenderWindow& window);
        std::string getText() const;

    private:
        sf::Font _font;
        sf::Text _text;
        std::string _rawText;

        float _startX, _endX, _startY, _endY;
        float _lineHeight = 22.f;

        void wrapText();
        int countLines(const std::string& str);
    };

}


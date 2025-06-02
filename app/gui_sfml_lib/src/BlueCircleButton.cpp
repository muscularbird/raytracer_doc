#include "../include/include.hpp"
#include "../include/BlueCircleButton.hpp"
#include <filesystem>
#include <iostream>

namespace Plazza::Components {

    BlueCircleButton::BlueCircleButton(const std::string& text, float radius)
            : _normalColor(sf::Color(30, 144, 255)),
              _hoverColor(sf::Color(0, 102, 204))
    {
        //std::filesystem::path fontPath = std::filesystem::current_path() / "assets/fonts/jetpack_font.ttf";
        std::filesystem::path fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
        if (!_font.loadFromFile(fontPath.string())) {
            std::cerr << "Erreur chargement police: " << fontPath << "\n";
        }

        _shape.setRadius(radius);
        _shape.setFillColor(_normalColor);
        _shape.setOrigin(radius, radius);

        _text.setFont(_font);
        _text.setString(text);
        _text.setCharacterSize(16);
        _text.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = _text.getLocalBounds();
        _text.setOrigin(textBounds.left + textBounds.width / 2.f,
                        textBounds.top + textBounds.height / 2.f);
    }

    void BlueCircleButton::setPosition(sf::Vector2f pos) {
        _shape.setPosition(pos);
        _text.setPosition(pos);
    }

    void BlueCircleButton::update(const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f center = _shape.getPosition();
        float radius = _shape.getRadius();
        float dist = std::hypot(mousePos.x - center.x, mousePos.y - center.y);

        if (dist <= radius) {
            _shape.setFillColor(_hoverColor);
        } else {
            _shape.setFillColor(_normalColor);
        }
    }

    void BlueCircleButton::draw(sf::RenderWindow& window) {
        window.draw(_shape);
        window.draw(_text);
    }

    bool BlueCircleButton::isClicked(const sf::RenderWindow& window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f center = _shape.getPosition();
            float radius = _shape.getRadius();
            float dist = std::hypot(mousePos.x - center.x, mousePos.y - center.y);
            return dist <= radius;
        }
        return false;
    }

}

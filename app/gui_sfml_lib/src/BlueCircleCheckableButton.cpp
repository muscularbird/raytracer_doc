#include "../include/include.hpp"
#include "../include/BlueCircleCheckableButton.hpp"
#include <filesystem>
#include <iostream>

namespace Plazza::Components {

    BlueCircleCheckableButton::BlueCircleCheckableButton(const std::string& text, float radius)
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

        _cross.setFont(_font);
        _cross.setString("X");
        _cross.setCharacterSize(24);
        _cross.setFillColor(sf::Color::Black);
        sf::FloatRect crossBounds = _cross.getLocalBounds();
        _cross.setOrigin(crossBounds.left + crossBounds.width / 2.f,
                         crossBounds.top + crossBounds.height / 2.f);

    }

    void BlueCircleCheckableButton::setPosition(sf::Vector2f pos) {
        _shape.setPosition(pos);
        _text.setPosition(pos);
        _cross.setPosition(pos);
    }

    void BlueCircleCheckableButton::update(const sf::RenderWindow& window) {
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

    void BlueCircleCheckableButton::draw(sf::RenderWindow& window) {
        window.draw(_shape);
        window.draw(_text);
        if (_active) {
            window.draw(_cross);
        }
    }


    bool BlueCircleCheckableButton::isClicked(const sf::RenderWindow& window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f center = _shape.getPosition();
            float radius = _shape.getRadius();
            float dist = std::hypot(mousePos.x - center.x, mousePos.y - center.y);
            return dist <= radius;
        }
        return false;
    }

    void BlueCircleCheckableButton::handleClick(const sf::RenderWindow& window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f center = _shape.getPosition();
            float radius = _shape.getRadius();
            float dist = std::hypot(mousePos.x - center.x, mousePos.y - center.y);
            if (dist <= radius) {
                _active = !_active;
                sf::sleep(sf::milliseconds(150));
            }
        }
    }

    bool BlueCircleCheckableButton::isActive() const {
        return _active;
    }

}

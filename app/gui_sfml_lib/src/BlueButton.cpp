#include "../include/include.hpp"
#include "../include/BlueButton.hpp"

namespace Plazza::Components {

    BlueButton::BlueButton(const std::string& text, sf::Vector2f size)
            : _normalColor(sf::Color(30, 144, 255)),
              _hoverColor(sf::Color(0, 102, 204))
    {
        //std::filesystem::path fontPath = std::filesystem::current_path() / "assets/fonts/jetpack_font.ttf";
        std::filesystem::path fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
        if (!_font.loadFromFile(fontPath.string())) {
            std::cerr << "Erreur chargement police: " << fontPath << "\n";
        }

        _shape.setSize(size);
        _shape.setFillColor(_normalColor);

        _text.setFont(_font);
        _text.setString(text);
        _text.setCharacterSize(18);
        _text.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = _text.getLocalBounds();
        _text.setOrigin(textBounds.left + textBounds.width / 2.f,
                        textBounds.top + textBounds.height / 2.f);
    }

    void BlueButton::setPosition(sf::Vector2f pos) {
        _shape.setPosition(pos);
        _text.setPosition(pos + _shape.getSize() / 2.f);
    }

    void BlueButton::update(const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (_shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            _shape.setFillColor(_hoverColor);
        } else {
            _shape.setFillColor(_normalColor);
        }
    }

    void BlueButton::draw(sf::RenderWindow& window) {
        window.draw(_shape);
        window.draw(_text);
    }

    bool BlueButton::isClicked(const sf::RenderWindow& window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            return _shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        }
        return false;
    }

}

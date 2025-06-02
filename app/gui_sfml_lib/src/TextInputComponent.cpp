#include "../include/TextInputComponent.hpp"
#include <iostream>
#include <filesystem>

namespace Plazza::Components {

    TextInputComponent::TextInputComponent(const std::string& placeholder)
            : _inputText(""), _startX(0), _endX(0), _y(0), _lineHeight(24.f)
    {
        //std::filesystem::path fontPath = std::filesystem::current_path() / "assets/fonts/jetpack_font.ttf";
        std::filesystem::path fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
        if (!_font.loadFromFile(fontPath.string())) {
            std::cerr << "Erreur chargement police: " << fontPath << "\n";
        }

        _displayText.setFont(_font);
        _displayText.setCharacterSize(20);
        _displayText.setFillColor(sf::Color::Black);

        _placeholderText.setFont(_font);
        _placeholderText.setCharacterSize(20);
        _placeholderText.setFillColor(sf::Color(150, 150, 150));
        _placeholderText.setString(placeholder);

        _box.setFillColor(sf::Color::Transparent);
        _box.setOutlineColor(sf::Color::White);
        _box.setOutlineThickness(1.f);
    }

    void TextInputComponent::setPosition(float startX, float endX, float startY, float endY) {
        _startX = startX;
        _endX = endX;
        _y = startY;
        _endY = endY;

        float width = endX - startX;
        float height = endY - startY;

        _box.setPosition({startX, startY});
        _box.setSize({width, height});

        _placeholderText.setPosition(startX + 5, startY + 2);
        wrapText();
    }

    int countLines(const std::string& text) {
        return std::count(text.begin(), text.end(), '\n') + 1;
    }

    void TextInputComponent::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) {
                if (!_inputText.empty()) {
                    _inputText.pop_back();
                    wrapText();
                }
            } else if (event.text.unicode >= 32 && event.text.unicode < 127) {
                std::string testInput = _inputText + static_cast<char>(event.text.unicode);

                std::string wrapped;
                std::string currentLine;
                float maxWidth = _endX - _startX - 10;

                _displayText.setString("");

                for (char c : testInput) {
                    std::string testLine = currentLine + c;
                    _displayText.setString(testLine);
                    float lineWidth = _displayText.getLocalBounds().width;

                    if (lineWidth > maxWidth && !currentLine.empty()) {
                        wrapped += currentLine + '\n';
                        currentLine = c;
                    } else {
                        currentLine += c;
                    }
                }

                wrapped += currentLine;
                int lines = countLines(wrapped);
                float totalHeight = lines * _lineHeight;

                if (_y + totalHeight <= _endY) {
                    _inputText += static_cast<char>(event.text.unicode);
                    wrapText();
                }
            }
        }
    }

    void TextInputComponent::wrapText() {
        std::string wrapped;
        std::string currentLine;
        float maxWidth = _endX - _startX - 10;

        _displayText.setString("");

        for (char c : _inputText) {
            std::string testLine = currentLine + c;
            _displayText.setString(testLine);

            float lineWidth = _displayText.getLocalBounds().width;

            if (lineWidth > maxWidth && !currentLine.empty()) {
                wrapped += currentLine + '\n';
                currentLine = c;
            } else {
                currentLine += c;
            }
        }

        wrapped += currentLine;
        _displayText.setString(wrapped);
        _displayText.setPosition(_startX + 5, _y + 2);
    }


    void TextInputComponent::draw(sf::RenderWindow& window) {
        window.draw(_box);
        if (_inputText.empty()) {
            window.draw(_placeholderText);
        } else {
            window.draw(_displayText);
        }
    }

    std::string TextInputComponent::getText() const {
        return _inputText;
    }

    void TextInputComponent::clear() {
        _inputText.clear();
        wrapText();
    }

    void TextInputComponent::setText(const std::string& text) {
        _inputText = text;
        wrapText();
    }

}

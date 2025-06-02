#include "../include/WhiteTexteComponent.hpp"
#include <iostream>
#include <filesystem>
#include <sstream>
#include <algorithm>

namespace Plazza::Components {

    WhiteTexteComponent::WhiteTexteComponent(const std::string& content)
            : _rawText(content), _startX(0), _endX(0), _startY(0), _endY(0)
    {
        //std::filesystem::path fontPath = std::filesystem::current_path() / "assets/fonts/jetpack_font.ttf";
        std::filesystem::path fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
        if (!_font.loadFromFile(fontPath.string())) {
            std::cerr << "Erreur chargement police: " << fontPath << "\n";
        }

        _text.setFont(_font);
        _text.setCharacterSize(20);
        _text.setFillColor(sf::Color::White);
    }

    void WhiteTexteComponent::setText(const std::string& content) {
        _rawText = content;
        wrapText();
    }

    void WhiteTexteComponent::setPosition(float startX, float endX, float startY, float endY) {
        _startX = startX;
        _endX = endX;
        _startY = startY;
        _endY = endY;

        wrapText();
    }

    int WhiteTexteComponent::countLines(const std::string& str) {
        return std::count(str.begin(), str.end(), '\n') + 1;
    }

    void WhiteTexteComponent::wrapText() {
        std::string wrapped;
        std::string currentLine;

        float maxWidth = _endX - _startX - 10;

        _text.setString("");

        for (char c : _rawText) {
            std::string testLine = currentLine + c;
            _text.setString(testLine);
            float lineWidth = _text.getLocalBounds().width;

            if (lineWidth > maxWidth && !currentLine.empty()) {
                wrapped += currentLine + '\n';
                currentLine = c;
            } else {
                currentLine += c;
            }
        }

        wrapped += currentLine;

        int totalLines = countLines(wrapped);
        float totalHeight = totalLines * _lineHeight;

        if (_startY + totalHeight <= _endY) {
            _text.setString(wrapped);
            _text.setPosition(_startX + 5, _startY + 2);
        } else {
            std::istringstream iss(wrapped);
            std::string line;
            std::string limitedText;
            int lineCount = 0;
            while (std::getline(iss, line)) {
                if ((lineCount + 1) * _lineHeight + _startY > _endY) break;
                limitedText += line + '\n';
                ++lineCount;
            }
            _text.setString(limitedText);
            _text.setPosition(_startX + 5, _startY + 2);
        }
    }

    void WhiteTexteComponent::draw(sf::RenderWindow& window) {
        window.draw(_text);
    }

    std::string WhiteTexteComponent::getText() const {
        return _rawText;
    }

}


#include "TextBoxPlaylist.h"

#include <iostream>

TextBoxPlaylist::TextBoxPlaylist() = default;

TextBoxPlaylist::TextBoxPlaylist(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                                 const sf::Color& textColor) : TextBox(box_, boxColor, font_, text_, textColor) {
    box.setOutlineThickness(1.0f);
    box.setOutlineColor(textColor);
}

/*void TextBoxPlaylist::changeActive(const sf::Vector2f& mousePosition) {
    if (box.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        isActive = !isActive;
        std::cout << isActive << std::endl;
    }
}

void TextBoxPlaylist::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            changeActive(mousePos);
        }
    }
}*/

TextBox* TextBoxPlaylist::clone() const {
    return new TextBoxPlaylist(*this);
}
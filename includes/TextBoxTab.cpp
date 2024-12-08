#include "TextBoxTab.h"

TextBoxTab::TextBoxTab() = default;

TextBoxTab::TextBoxTab(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                       const sf::Color& textColor) : TextBox(box_, boxColor, font_, text_, textColor) {
    box.setOutlineThickness(1.0f);
    box.setOutlineColor(textColor);
}

// cppcheck-suppress unusedFunction ; false positive
bool TextBoxTab::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (box.getGlobalBounds().contains(mousePos)) {
            onClickCallback();
            isActive = true;
            return true;
        }
    }
    isActive = false;
    return false;
}

// cppcheck-suppress unusedFunction ; false positive
void TextBoxTab::setOnClickCallback(const std::function<void()>& callback) {
    onClickCallback = callback;
}

void TextBoxTab::draw(sf::RenderWindow& window) const {
    TextBox::draw(window);
    if (isActive) {
        sf::RectangleShape border = box;
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(1);
        window.draw(border);
        window.draw(text);
    }
}

TextBox* TextBoxTab::clone() const {
    return new TextBoxTab(*this);
}

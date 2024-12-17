#include "TextBoxTab.h"

void TextBoxTab::extraDraw(sf::RenderWindow& window) {
    if (isActive) {
        sf::RectangleShape border = box;
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(1);
        window.draw(border);
        window.draw(text);
    }
}

TextBoxTab::TextBoxTab() = default;

TextBoxTab::TextBoxTab(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                       const sf::Color& textColor) : TextBox(box_, boxColor, font_, text_, textColor) {
    box.setOutlineThickness(1.0f);
    box.setOutlineColor(textColor);
}

// cppcheck-suppress unusedFunction ; false positive
void TextBoxTab::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (box.getGlobalBounds().contains(mousePos)) {
            onClickCallback();
            isActive = true;
            return;
        }
    }
    isActive = false;
}

// cppcheck-suppress unusedFunction ; false positive
void TextBoxTab::setOnClickCallback(const std::function<void()>& callback) {
    onClickCallback = callback;
}

TextBoxTab* TextBoxTab::clone() const {
    return new TextBoxTab(*this);
}

TextBoxTab& TextBoxTab::operator=(const TextBoxTab& other) {
    TextBoxTab* temp = other.clone();
    swap(*this, *temp);
    delete temp;
    return *this;
}

void swap(TextBoxTab& t1, TextBoxTab& t2) noexcept {
    using std::swap;
    swap(t1.font, t2.font);
    swap(t1.box, t2.box);
    swap(t1.text, t2.text);
    swap(t1.isActive, t2.isActive);
    swap(t1.onClickCallback, t2.onClickCallback);
}

TextBoxTab::TextBoxTab(const TextBoxTab& other) = default;

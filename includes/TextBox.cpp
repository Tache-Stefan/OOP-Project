#include "TextBox.h"

TextBox::TextBox(sf::RectangleShape box_, const sf::Color& boxColor, const sf::Font& font_, sf::Text text_,
                 const sf::Color& textColor) : font(font_), box(std::move(box_)), text(std::move(text_)) {
    box.setFillColor(boxColor);
    text.setFont(font);
    text.setFillColor(textColor);
}

TextBox::TextBox() = default;

// cppcheck-suppress unusedFunction ; false positive
void TextBox::centerShape(const sf::RenderWindow& window) {
    const sf::FloatRect boxBounds = box.getGlobalBounds();
    box.setPosition(
        window.getSize().x / 2.0f - boxBounds.width / 2.0f,
        window.getSize().y / 2.0f - boxBounds.height / 2.0f
    );

    const sf::FloatRect textBounds = text.getLocalBounds();

    text.setPosition(
        box.getPosition().x + 10,
        box.getPosition().y + (box.getSize().y - textBounds.height) / 2 - textBounds.top
    );
}

// cppcheck-suppress unusedFunction ; false positive
void TextBox::positionShape(const sf::Vector2f& boxPosition, const sf::Vector2f& textPosition) {
    box.setPosition(boxPosition);
    text.setPosition(textPosition);
}

// cppcheck-suppress unusedFunction ; false positive
void TextBox::setText(const std::string& userInput) { text.setString(userInput); }

void TextBox::draw(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(text);
}

TextBox* TextBox::clone() const {
    return new TextBox(*this);
}

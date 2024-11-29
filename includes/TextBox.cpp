#include "TextBox.h"

#include <iostream>

TextBox::TextBox(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                 const sf::Color& textColor) : font(font_), box(box_), text(text_) {
    box.setFillColor(boxColor);
    text.setFont(font);
    text.setFillColor(textColor);
}

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

void TextBox::setText(const std::string& userInput) { text.setString(userInput); }

void TextBox::draw(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(text);
}

void TextBox::handleEvents(sf::RenderWindow& window, const sf::Event& event, std::atomic<bool>& stopPlayback,
                              std::atomic<bool>& isMusicPlaying, std::string& userInput) {
    std::cout << "Test" << std::endl;
}

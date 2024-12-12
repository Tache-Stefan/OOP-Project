#include "TextBoxButton.h"

#include "MusicPlayer.h"

TextBoxButton::TextBoxButton(sf::RectangleShape box_, const sf::Color& boxColor, const sf::Font& font_, sf::Text text_,
                             const sf::Color& textColor) : TextBox(std::move(box_), boxColor, font_, std::move(text_), textColor),
                             originalColor(boxColor) {}

void TextBoxButton::setOnClickCallback(const std::function<void()>& callback) {
    onClickCallback = callback;
}

bool TextBoxButton::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    if (!MusicPlayer::getIsMusicPlaying()) {
        box.setFillColor(sf::Color(150, 150, 150));
        isActive = false;
        return false;
    }
    box.setFillColor(originalColor);

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

void TextBoxButton::draw(sf::RenderWindow& window) const {
    TextBox::draw(window);
    if (isActive) {
        sf::RectangleShape border = box;
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(1);
        window.draw(border);
        window.draw(text);
    }
}

TextBoxButton* TextBoxButton::clone() const {
    return new TextBoxButton(*this);
}

TextBoxButton& TextBoxButton::operator=(const TextBoxButton& other) {
    TextBoxButton* temp = other.clone();
    swap(*this, *temp);
    delete temp;
    return *this;
}

void swap(TextBoxButton& t1, TextBoxButton& t2) noexcept {
    using std::swap;
    swap(t1.font, t2.font);
    swap(t1.box, t2.box);
    swap(t1.text, t2.text);
    swap(t1.isActive, t2.isActive);
    swap(t1.onClickCallback, t2.onClickCallback);
    swap(t1.originalColor, t2.originalColor);
}

TextBoxButton::TextBoxButton(const TextBoxButton& other) : TextBox(other), isActive(other.isActive),
                                                           onClickCallback(other.onClickCallback), originalColor(other.originalColor) {}

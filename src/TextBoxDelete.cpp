#include "../headers/TextBoxDelete.h"

#include <memory>

#include "../headers/Song.h"

TextBoxDelete::TextBoxDelete() = default;

TextBoxDelete::TextBoxDelete(sf::RectangleShape box_, const sf::Font& font_, sf::Text text_)
                             : TextBox(std::move(box_), sf::Color::Red, font_, std::move(text_), sf::Color::White) {
    text.setString("X");
    text.setCharacterSize(34);
    box.setOutlineThickness(0.5f);
    box.setOutlineColor(sf::Color::White);
}

void TextBoxDelete::handleEvents(sf::RenderWindow &, const sf::Event &) {}

TextBoxDelete* TextBoxDelete::clone() const {
    return new TextBoxDelete(*this);
}

TextBoxDelete& TextBoxDelete::operator=(const TextBoxDelete& other) {
    TextBoxDelete* temp = other.clone();
    swap(*this, *temp);
    delete temp;
    return *this;
}

void swap(TextBoxDelete& t1, TextBoxDelete& t2) noexcept {
    using std::swap;
    swap(t1.font, t2.font);
    swap(t1.box, t2.box);
    swap(t1.text, t2.text);
}

TextBoxDelete::TextBoxDelete(const TextBoxDelete& other) = default;

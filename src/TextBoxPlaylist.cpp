#include "../headers/TextBoxPlaylist.h"

TextBoxPlaylist::TextBoxPlaylist() = default;

TextBoxPlaylist::TextBoxPlaylist(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                                 const sf::Color& textColor) : TextBox(box_, boxColor, font_, text_, textColor) {
    box.setOutlineThickness(1.0f);
    box.setOutlineColor(textColor);
}

void TextBoxPlaylist::handleEvents(sf::RenderWindow &, const sf::Event &) {}

TextBoxPlaylist* TextBoxPlaylist::clone() const {
    return new TextBoxPlaylist(*this);
}

TextBoxPlaylist& TextBoxPlaylist::operator=(const TextBoxPlaylist& other) {
    TextBoxPlaylist* temp = other.clone();
    swap(*this, *temp);
    delete temp;
    return *this;
}

void swap(TextBoxPlaylist& t1, TextBoxPlaylist& t2) noexcept {
    using std::swap;
    swap(t1.font, t2.font);
    swap(t1.box, t2.box);
    swap(t1.text, t2.text);
}

TextBoxPlaylist::TextBoxPlaylist(const TextBoxPlaylist& other) = default;

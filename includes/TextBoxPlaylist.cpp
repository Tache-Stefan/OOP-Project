#include "TextBoxPlaylist.h"

TextBoxPlaylist::TextBoxPlaylist() = default;

TextBoxPlaylist::TextBoxPlaylist(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                                 const sf::Color& textColor) : TextBox(box_, boxColor, font_, text_, textColor) {
    box.setOutlineThickness(1.0f);
    box.setOutlineColor(textColor);
}

TextBox* TextBoxPlaylist::clone() const {
    return new TextBoxPlaylist(*this);
}
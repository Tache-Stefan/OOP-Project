#pragma once
#include "TextBox.h"

class TextBoxPlaylist : public TextBox {
public:
    TextBoxPlaylist();
    TextBoxPlaylist(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                    const sf::Color& textColor);
    TextBox* clone() const override;
};

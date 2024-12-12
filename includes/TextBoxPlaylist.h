#pragma once
#include "TextBox.h"

class TextBoxPlaylist : public TextBox {
public:
    TextBoxPlaylist();
    TextBoxPlaylist(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                    const sf::Color& textColor);
    TextBoxPlaylist* clone() const override;
    TextBoxPlaylist& operator=(const TextBoxPlaylist &other);
    friend void swap(TextBoxPlaylist& t1, TextBoxPlaylist& t2) noexcept;
};

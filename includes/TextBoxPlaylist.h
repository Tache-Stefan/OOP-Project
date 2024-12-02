#pragma once
#include "TextBox.h"

class TextBoxPlaylist : public TextBox {
private:
    //bool isActive = false;
public:
    TextBoxPlaylist();
    TextBoxPlaylist(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                    const sf::Color& textColor);
    /*void changeActive(const sf::Vector2f &mousePosition);
    void handleEvents(sf::RenderWindow &window, const sf::Event &event);*/
    TextBox* clone() const override;
};

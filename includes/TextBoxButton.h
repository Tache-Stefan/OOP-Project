#pragma once

#include <functional>

#include "TextBox.h"

class TextBoxButton : public TextBox {
private:
    bool isActive = false;
    std::function<void()> onClickCallback;
    sf::Color originalColor;
public:
    TextBoxButton(sf::RectangleShape box_, const sf::Color& boxColor, const sf::Font& font_, sf::Text text_,
                  const sf::Color& textColor);
    void setOnClickCallback(const std::function<void()> &callback);
    bool handleEvents(sf::RenderWindow &window, const sf::Event &event);
    void draw(sf::RenderWindow &window) const override;
    TextBox* clone() const override;
};

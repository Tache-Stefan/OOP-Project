#pragma once
#include <functional>

#include "TextBox.h"

class TextBoxTab : public TextBox {
private:
    bool isActive = false;
    std::function<void()> onClickCallback;
public:
    TextBoxTab(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
               const sf::Color& textColor);
    bool handleEvents(const sf::Event& event, const sf::RenderWindow& window);
    void setOnClickCallback(const std::function<void()>& callback);
    void draw(sf::RenderWindow &window) const override;
};

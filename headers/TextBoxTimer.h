#pragma once

#include "TextBox.h"

class TextBoxTimer : public TextBox {
private:
    sf::Time elapsedTime;
    sf::Time totalDuration;
    std::string formatTime(const sf::Time& time) const;
    void updateText();
    void extraDraw(sf::RenderWindow &window) override;
public:
    TextBoxTimer(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                 const sf::Color& textColor);
    void updateTime();
    void handleEvents(sf::RenderWindow&, const sf::Event&) override;
    TextBoxTimer* clone() const override;
};

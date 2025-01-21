#pragma once
#include "TextBox.h"

class TextBoxVolume : public TextBox {
private:
    int currentVolume = 0;
    const int maxVolume = 100;
    void extraDraw(sf::RenderWindow &window) override;
    void updateText();
public:
    TextBoxVolume(const sf::RectangleShape &box_, const sf::Color &boxColor, const sf::Font &font_,
                           const sf::Text &text_, const sf::Color &textColor);
    void handleEvents(sf::RenderWindow &, const sf::Event &) override;
    TextBoxVolume* clone() const override;
};

#pragma once

#include <SFML/Graphics.hpp>

class TextBox {
protected:
    sf::Font font;
    sf::RectangleShape box;
    sf::Text text;
public:
    virtual ~TextBox() = default;
    TextBox();
    TextBox(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
            const sf::Color& textColor);
    void centerShape(const sf::RenderWindow& window);
    void setText(const std::string& userInput);
    virtual void draw(sf::RenderWindow& window) const;
};

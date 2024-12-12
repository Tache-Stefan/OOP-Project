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
    TextBox(sf::RectangleShape box_, const sf::Color& boxColor, const sf::Font& font_, sf::Text text_,
            const sf::Color& textColor);
    void centerShape(const sf::RenderWindow& window);
    void positionShape(const sf::Vector2f& boxPosition, const sf::Vector2f& textPosition);
    void setText(const std::string& userInput);
    virtual void draw(sf::RenderWindow& window) const;
    virtual TextBox* clone() const = 0;
    friend void swap(TextBox& t1, TextBox& t2) noexcept;
};

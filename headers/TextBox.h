#pragma once

#include <SFML/Graphics.hpp>

class TextBox {
private:
    virtual void drawRequirement([[maybe_unused]] sf::RenderWindow&, [[maybe_unused]] bool& ok) {}
    virtual void extraDraw([[maybe_unused]] sf::RenderWindow& window) {}
protected:
    sf::Font font;
    sf::RectangleShape box;
    sf::Text text;
    friend void swap(TextBox& t1, TextBox& t2) noexcept;
    TextBox(const TextBox &other);
public:
    virtual ~TextBox() = default;
    TextBox();
    TextBox(sf::RectangleShape box_, const sf::Color& boxColor, const sf::Font& font_, sf::Text text_,
            const sf::Color& textColor);
    void centerShape(const sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void positionShape(const sf::Vector2f& boxPosition, const sf::Vector2f& textPosition);
    void setText(const std::string& userInput);
    virtual void handleEvents(sf::RenderWindow&, const sf::Event&) = 0;
    virtual void draw(sf::RenderWindow& window);
    virtual TextBox* clone() const = 0;
};

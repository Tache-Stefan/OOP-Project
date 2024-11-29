#pragma once
#include <atomic>

#include "SFML/Graphics.hpp"

class TextBox {
private:
    sf::Font font;
protected:
    sf::RectangleShape box;
    sf::Text text;
public:
    virtual ~TextBox() = default;
    TextBox(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
            const sf::Color& textColor);
    void centerShape(const sf::RenderWindow& window);
    void setText(const std::string& userInput);
    virtual void draw(sf::RenderWindow& window) const;
    virtual void handleEvents(sf::RenderWindow& window, const sf::Event& event, std::atomic<bool>& stopPlayback,
                              std::atomic<bool>& isMusicPlaying, std::string& userInput);
};

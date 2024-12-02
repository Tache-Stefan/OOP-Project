#pragma once
#include "TextBox.h"

#include <atomic>
#include <SFML/Graphics.hpp>

class TextBoxWrite : public TextBox {
private:
    bool isActive = false;
public:
    TextBoxWrite(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_, const sf::Color& textColor);
    bool containsClick(const sf::Vector2f& mousePosition);
    void handleEvents(sf::RenderWindow& window, const sf::Event& event, std::atomic<bool>& stopPlayback,
                      std::atomic<bool>& isMusicPlaying, std::string& userInput);
    void searchAndPlay(std::atomic<bool>& stopPlayback, std::atomic<bool>& isMusicPlaying);
    void draw(sf::RenderWindow& window) const override;
    void draw(sf::RenderWindow& window, std::atomic<bool>& isMusicPlaying) const;
    bool getActive() const;
};

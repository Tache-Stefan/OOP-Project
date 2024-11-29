#pragma once
#include <atomic>

#include <SFML/Graphics.hpp>
#include "TextBox.h"

class TextBoxWrite : public TextBox {
private:
    bool isActive = false;
public:
    TextBoxWrite(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_, const sf::Color& textColor);
    bool containsClick(const sf::Vector2f& mousePosition);
    bool getActive() const;
    void handleEvents(sf::RenderWindow& window, const sf::Event& event, std::atomic<bool>& stopPlayback,
                      std::atomic<bool>& isMusicPlaying, std::string& userInput) override;
    void searchAndPlay(std::atomic<bool>& stopPlayback, std::atomic<bool>& isMusicPlaying);
};

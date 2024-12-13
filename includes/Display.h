#pragma once

#include <SFML/Graphics.hpp>

#include "TextBoxWrite.h"

class Display {
private:
    virtual void setMaxScroll(int& maxScroll) = 0;
protected:
    sf::Font font;
    TextBoxWrite inputBox;
    sf::Text inputText;
    std::array<sf::RectangleShape, 8> textsRects;
    std::array<sf::Text, 8> texts;
    std::array<sf::RectangleShape, 8> deleteRects;
    float scrollSpeed;
    float verticalOffset;
    unsigned int visibleCount;
    int itemHeight;
    float windowWidth;
    float windowHeight;
public:
    explicit Display(const sf::Font& font_);
    virtual ~Display() = default;
    virtual void scrollUp();
    virtual void scrollDown();
    virtual void scrollWithMouse(float delta);
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvents(sf::RenderWindow& window, const sf::Event& event, Playlist* playlist = nullptr) = 0;
    virtual Display* clone() const = 0;
};

#include "../headers/Display.h"

Display::Display(const sf::Font &font_) : font(font_),
    inputBox(TextBoxWrite(sf::RectangleShape(sf::Vector2f(300.f, 50.f)), sf::Color::White, font,
   sf::Text("", font, 24), sf::Color::Black)),
    scrollSpeed(40.f), verticalOffset(0.f), visibleCount(8), itemHeight(40),
    windowWidth(1200), windowHeight(700) {

    for (unsigned int i = 0; i < 8; ++i) {
        textsRects[i] = sf::RectangleShape(sf::Vector2f(200, 40));
        texts[i] = sf::Text("", font, 24);
        deleteRects[i] = sf::RectangleShape(sf::Vector2f(60, 40));
    }
}

void Display::scrollUp() {
    if (verticalOffset > 0) {
        verticalOffset -= scrollSpeed;
    }
}

void Display::scrollDown() {
    int maxScroll;
    setMaxScroll(maxScroll);

    if (verticalOffset < maxScroll) {
        verticalOffset += scrollSpeed;
    }
    if (verticalOffset > maxScroll) {
        verticalOffset = maxScroll;
    }
}

void Display::scrollWithMouse(const float delta) {
    if (delta < 0) {
        scrollDown();
    } else if (delta > 0) {
        scrollUp();
    }
}
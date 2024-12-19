#pragma once

#include <SFML/Graphics.hpp>
#include "DisplayManager.h"
#include "TextBoxManager.h"

class Application {
private:
    TextBoxManager textBoxManager;
    DisplayManager displayManager;
    sf::Font font;
    int currentTab;
    sf::RenderWindow window;
    void handleEvents();
    void render();
public:
    explicit Application(const sf::Font& font_);
    void run();
    ~Application();
};

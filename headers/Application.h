#pragma once

#include <SFML/Graphics.hpp>
#include "DisplayManager.h"
#include "TextBoxConcreteFactory.h"
#include "TextBoxManager.h"

class Application {
private:
    std::unique_ptr<TextBoxAbstractFactory> factory = std::make_unique<TextBoxConcreteFactory>();
    TextBoxManager textBoxManager;
    DisplayManager displayManager;
    sf::Font font;
    int currentTab;
    sf::RenderWindow window;
    void createUI();
    void handleEvents();
    void render();
public:
    explicit Application(const sf::Font& font_);
    void run();
    ~Application();
};

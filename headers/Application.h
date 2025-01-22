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
    static int currentTab;
    sf::RenderWindow window;
    void createUI();
    void handleEvents();
    void render();
    explicit Application(const sf::Font& font_);
public:
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    static Application& getInstance(const sf::Font& font_);
    static int getCurrentTab();
    void run();
    ~Application();
};

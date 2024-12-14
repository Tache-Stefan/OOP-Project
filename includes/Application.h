#pragma once

#include <SFML/Graphics.hpp>

#include "Display.h"
#include "TextBoxButton.h"
#include "TextBoxTab.h"
#include "TextBoxWrite.h"

class Application {
private:
    sf::Font font;
    int currentTab;
    sf::RenderWindow window;
    TextBoxWrite inputMusic;
    std::vector<TextBoxTab> tabs;
    std::vector<TextBoxButton> buttons;
    std::vector<TextBoxButton> volButtons;
    std::unique_ptr<Display> display;
    void resizeUI(float windowWidth, float windowHeight);
    void handleEvents();
    void render();
public:
    explicit Application(const sf::Font& font_);
    void run();
    ~Application();
};

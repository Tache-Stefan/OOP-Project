#pragma once

#include <SFML/Graphics.hpp>

#include "Display.h"
#include "TextBoxButton.h"
#include "TextBoxWrite.h"

class Application {
private:
    sf::Font font;
    int currentTab;
    sf::RenderWindow window;
    TextBoxWrite inputMusic;
    std::vector<std::unique_ptr<TextBox>> tabs;
    std::vector<std::unique_ptr<TextBox>> buttons;
    std::vector<std::unique_ptr<TextBox>> volButtons;
    std::unique_ptr<Display> display;
    void drawTextBox(const std::unique_ptr<TextBox>& textBox);
    void resizeUI(float windowWidth, float windowHeight) const;
    void handleEvents();
    void render();
public:
    explicit Application(const sf::Font& font_);
    void run();
    ~Application();
};

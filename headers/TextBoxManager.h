#pragma once
#include <memory>
#include <vector>

#include "TextBox.h"

class TextBoxManager {
private:
    std::vector<std::unique_ptr<TextBox>> textBoxes;
public:
    TextBoxManager();
    void addTextBox(std::unique_ptr<TextBox> textBox);
    void addVectorTextBox(std::vector<std::unique_ptr<TextBox>> textBoxes_);
    void draw(int currentTab, sf::RenderWindow& window);
    void resizeUI(const sf::RenderWindow &window, float windowWidth, float windowHeight) const;
    void handleEvents(const int currentTab, sf::RenderWindow &window, const sf::Event &event);
};

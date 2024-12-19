#pragma once
#include <memory>
#include <vector>

#include "Display.h"

class DisplayManager {
private:
    std::vector<std::unique_ptr<Display>> displays;
public:
    DisplayManager();
    void addDisplay(std::unique_ptr<Display> display);
    void draw(const int currentTab, sf::RenderWindow& window);
    void handleEvents(int currentTab, sf::RenderWindow &window, const sf::Event &event);
    ~DisplayManager();
};

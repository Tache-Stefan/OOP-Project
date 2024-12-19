#include "../headers/DisplayManager.h"

#include <iostream>

#include "../headers/Exceptions.h"
#include "../headers/PlaylistDisplay.h"

DisplayManager::DisplayManager() = default;

void DisplayManager::addDisplay(std::unique_ptr<Display> display) {
    displays.emplace_back(std::move(display));
}

void DisplayManager::draw(const int currentTab, sf::RenderWindow &window) {
    for (const auto &display : displays) {
        if (currentTab == 2)
            display->draw(window);
    }
}

void DisplayManager::handleEvents(const int currentTab, sf::RenderWindow &window, const sf::Event& event) {
    for (const auto &display : displays) {
        if (currentTab == 2)
            display->handleEvents(window, event, nullptr);
    }
}

DisplayManager::~DisplayManager() {
    for (const auto &display : displays) {
        if (const auto playlistDisplay = dynamic_cast<PlaylistDisplay*>(display.get()))
            try {
                playlistDisplay->savePlaylists();
            } catch (const FileException &e) {
                std::cout << e.what() << std::endl;
            }
    }
}


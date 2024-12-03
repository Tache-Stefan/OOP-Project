#include <iostream>
#include <fstream>
#include <string>
#include <atomic>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "includes/Utility.h"
#include "includes/EnvironmentSetup.h"
#include "includes/PlaylistDisplay.h"
#include "includes/SongDisplay.h"
#include "includes/TextBoxTab.h"
#include "includes/TextBoxWrite.h"

int main() {
    const EnvironmentSetup envSetup;

    sf::RenderWindow window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default);
    window.setFramerateLimit(30);

    int currentTab = 1;

    sf::Font font;
    if (!font.loadFromFile("fonts/Franie-Regular.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    TextBoxWrite inputMusic(sf::RectangleShape(sf::Vector2f(400, 50)), sf::Color::White, font,
        sf::Text("", font, 24), sf::Color::Black);

    TextBoxTab searchTab = Utils::initSearchTab(font);
    TextBoxTab playlistsTab = Utils::initPlaylistsTab(font);

    searchTab.setOnClickCallback([&currentTab] {
        currentTab = 1;
    });
    playlistsTab.setOnClickCallback([&currentTab] {
        currentTab = 2;
    });

    PlaylistDisplay playlistDisplay(font);
    std::atomic<bool> stopPlayback(false);
    std::atomic<bool> isMusicPlaying(false);

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stopPlayback = true;
                window.close();
            }

            if (!inputMusic.getActive() && isMusicPlaying && event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::S) {
                stopPlayback = true;
                std::cout << "Playback stopped!" << std::endl;
            }

            if (currentTab == 1) {
                inputMusic.handleEventsMusic(window, event, stopPlayback, isMusicPlaying);
            }
            if (currentTab == 2) {
                playlistDisplay.handleEvents(window, event);
            }
            searchTab.handleEvents(window, event);
            playlistsTab.handleEvents(window, event);
        }

        switch (currentTab) {
            case 1:
                window.clear();
                inputMusic.centerShape(window);
                inputMusic.draw(window, isMusicPlaying);
                searchTab.draw(window);
                playlistsTab.draw(window);
                window.display();
            break;
            case 2:
                window.clear();
                playlistDisplay.draw(window);
                searchTab.draw(window);
                playlistsTab.draw(window);
                window.display();
            break;
            default:
                window.clear();
                searchTab.draw(window);
                playlistsTab.draw(window);
                window.display();
            break;
        }
    }

    return 0;
}

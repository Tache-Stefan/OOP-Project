#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "includes/Utility.h"
#include "includes/EnvironmentSetup.h"
#include "includes/Exceptions.h"
#include "includes/MusicPlayer.h"
#include "includes/PlaylistDisplay.h"
#include "includes/SongDisplay.h"
#include "includes/TextBoxTab.h"
#include "includes/TextBoxWrite.h"

int main() {
    const EnvironmentSetup envSetup;
    int currentTab = 1;

    sf::RenderWindow window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default);
    window.setFramerateLimit(30);

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

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                MusicPlayer::setStopPlayback(true);
                window.close();
            }

            if (!inputMusic.getActive() && MusicPlayer::getIsMusicPlaying() && event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::S) {
                MusicPlayer::setStopPlayback(true);
                std::cout << "Playback stopped!" << std::endl;
            }

            if (currentTab == 1) {
                try {
                    inputMusic.handleEventsMusic(window, event);
                } catch (const SearchException& e) {
                    std::cerr << e.what() << std::endl;
                }
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
                inputMusic.drawSearch(window);
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

    std::cout << "App closed." << std::endl;
    return 0;
}

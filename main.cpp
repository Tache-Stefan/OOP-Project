#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "includes/Utility.h"
#include "includes/EnvironmentSetup.h"
#include "includes/Exceptions.h"
#include "includes/MusicPlayer.h"
#include "includes/PlaylistDisplay.h"
#include "includes/TextBoxButton.h"
#include "includes/TextBoxTab.h"
#include "includes/TextBoxWrite.h"

int main() {
    EnvironmentSetup::getInstance();
    int currentTab = 1;

    sf::RenderWindow window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default);
    window.setFramerateLimit(30);

    sf::Font font;
    if (!font.loadFromFile("fonts/Franie-Regular.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    TextBoxWrite inputMusic(sf::RectangleShape(sf::Vector2f(400, 50)), sf::Color::White, font,
        sf::Text("", font, 24), sf::Color::Black);

    std::vector<TextBoxTab> tabs = Utils::initTabs(font, currentTab);
    std::vector<TextBoxButton> buttons = Utils::initButtons();
    std::unique_ptr<Display> display = std::make_unique<PlaylistDisplay>(font);

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                MusicPlayer::setStopPlayback(true);
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                auto windowWidth = static_cast<float>(event.size.width);
                auto windowHeight = static_cast<float>(event.size.height);

                for (unsigned int i = 0; i < 5; ++i) {
                    buttons[i].positionShape(
                        sf::Vector2f(windowWidth * 0.335 + i * 85, windowHeight * 0.615),
                        sf::Vector2f(windowWidth * 0.335 + 17 + i * 85, windowHeight * 0.615));
                }
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
                for (unsigned int i = 0; i < 5; ++i) {
                    buttons[i].handleEvents(window, event);
                }
            }
            if (currentTab == 2) {
                display->handleEvents(window, event);
            }
            for (unsigned int i = 0; i < 2; ++i) {
                tabs[i].handleEvents(window, event);
            }
        }

        window.clear();
        for (unsigned int i = 0; i < 2; ++i) {
            tabs[i].draw(window);
        }

        switch (currentTab) {
            case 1:
                inputMusic.centerShape(window);
                inputMusic.drawSearch(window);
                for (unsigned int i = 0; i < 5; ++i) {
                    buttons[i].draw(window);
                }
                window.display();
            break;
            case 2:
                display->draw(window);
                window.display();
            break;
            default:
                window.display();
            break;
        }
    }

    std::cout << "App closed." << std::endl;
    return 0;
}

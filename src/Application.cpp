#include "../headers/Application.h"

#include <iostream>

#include "../headers/EnvironmentSetup.h"
#include "../headers/MusicPlayer.h"
#include "../headers/Utility.h"
#include "../headers/PlaylistDisplay.h"
#include "../headers/TextBoxButton.h"

class TextBoxButton;

Application::Application(const sf::Font& font_) : font(font_), currentTab(1),
                                                  window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default) {
    window.setFramerateLimit(30);

    EnvironmentSetup::getInstance();
    displayManager.addDisplay(std::make_unique<PlaylistDisplay>(font));
    createUI();
}

std::function<void()> Application::getButtonCallback(const unsigned int i) {
    switch (i) {
        case 0: return [] { MusicPlayer::setSeekToStart(true); };
        case 1: return [] { MusicPlayer::setSkipBack(true); };
        case 2: return [] {
            if (MusicPlayer::getPaused()) {
                MusicPlayer::setPaused(false);
            } else {
                MusicPlayer::setPaused(true);
            }
        };
        case 3: return [] { MusicPlayer::setSkipForward(true); };
        case 4: return [] { MusicPlayer::setSeekToEnd(true); };
        default: return [] {};
    }
}

void Application::createUI() {
    sf::Font fontButtons;
    if (!fontButtons.loadFromFile("fonts/Coolvetica.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    textBoxManager.addTextBox(factory->createWrite(font));

    const std::array<std::string, 5> buttonLabels = {"|<", "<", "| |", ">", ">|"};
    for (unsigned int i = 0; i < buttonLabels.size(); ++i) {
        auto textBox = factory->createButton(fontButtons, buttonLabels[i]);
        if (auto* button = dynamic_cast<TextBoxButton*>(textBox.get())) {
            button->setOnClickCallback(getButtonCallback(i));
        }

        textBox->positionShape(
                sf::Vector2f(1200 * 0.335 + i * 85, 700 * 0.615),
                sf::Vector2f(1200 * 0.335 + 17 + i * 85, 700 * 0.615)
            );
        textBoxManager.addTextBox(std::move(textBox));
    }

    const std::array<std::string, 2> volLabels = {"VOL-", "VOL+"};
    for (unsigned int i = 0; i < volLabels.size(); ++i) {
        const float offsetX = 1200 - (80 + 80 * (1 - i));
        const float offsetY = 700 - 40;

        auto textBox = factory->createVolButton(fontButtons, volLabels[i]);
        if (auto* button = dynamic_cast<TextBoxButton*>(textBox.get())) {
            button->setOnClickCallback(volLabels[i] == "VOL-" ?
            [] { MusicPlayer::decreaseVolume(); } :
            [] { MusicPlayer::increaseVolume(); }
            );
        }

        textBox->positionShape(
                sf::Vector2f(offsetX, offsetY),
                sf::Vector2f(offsetX + 10, offsetY));
        textBoxManager.addTextBox(std::move(textBox));
    }

    const std::array<std::string, 2> tabLabels = {"Music player", "Playlists"};
    for (unsigned int i = 0; i < tabLabels.size(); ++i) {
        auto textBox = factory->createTab(font, tabLabels[i]);
        if (auto* tab = dynamic_cast<TextBoxTab*>(textBox.get())) {
            tab->setOnClickCallback([i, this] {
                    currentTab = i + 1;
                });
        }

        textBox->positionShape(
            sf::Vector2f(i * 200, 0),
            sf::Vector2f(20 + i * 230, 12)
            );
        textBoxManager.addTextBox(std::move(textBox));
    }
}

void Application::handleEvents() {
    sf::Event event{};

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            MusicPlayer::setStopPlayback(true);
            window.close();
        }

        if (event.type == sf::Event::Resized) {
            textBoxManager.resizeUI(window, event.size.width, event.size.height);
        }

        textBoxManager.handleEvents(currentTab, window, event);
        displayManager.handleEvents(currentTab, window, event);
    }
}

void Application::render() {
    window.clear();
    textBoxManager.draw(currentTab, window);
    displayManager.draw(currentTab, window);
    window.display();
}

void Application::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

Application::~Application() {
    std::cout << "App closed." << std::endl;
}

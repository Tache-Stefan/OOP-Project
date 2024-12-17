#include "../headers/Application.h"

#include <iostream>

#include "../headers/Exceptions.h"
#include "../headers/EnvironmentSetup.h"
#include "../headers/MusicPlayer.h"
#include "../headers/Utility.h"
#include "../headers/PlaylistDisplay.h"

void Application::drawTextBox(const std::unique_ptr<TextBox>& textBox) {
    if (textBox == nullptr)
        return;
    if (auto* mainWrite = dynamic_cast<TextBoxWrite*>(textBox.get())) {
        if (currentTab == 1)
            mainWrite->drawSearch(window);
    }
    else
        textBox->draw(window);
}

void Application::resizeUI(const float windowWidth, const float windowHeight) const {
    const sf::FloatRect bounds = inputMusic->getBounds();
    for (unsigned int i = 0; i < 5; ++i) {
        buttons[i]->positionShape(
        sf::Vector2f(window.getSize().x / 2.0f - bounds.width / 2.0f + i * 85,
                window.getSize().y / 2.0f - bounds.height / 2.0f + 100),
                sf::Vector2f(window.getSize().x / 2.0f - bounds.width / 2.0f + 17 + i * 85,
                window.getSize().y / 2.0f - bounds.height / 2.0f + 100));
    }
    for (int i = 1; i >= 0; --i) {
        volButtons[i == 1 ? 0 : 1]->positionShape(
        sf::Vector2f(windowWidth - (i + 1) * 80, windowHeight - 40),
        sf::Vector2f(windowWidth + 10 - (i + 1) * 80, windowHeight - 40));
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
            resizeUI(event.size.width, event.size.height);
        }

        if (currentTab == 1) {
            try {
                inputMusic->handleEvents(window, event);
            } catch (const SearchException& e) {
                std::cerr << e.what() << std::endl;
            }
            for (unsigned int i = 0; i < 5; ++i) {
                buttons[i]->handleEvents(window, event);
                if (i < 2) {
                    volButtons[i]->handleEvents(window, event);
                }
            }
        }
        if (currentTab == 2) {
            display->handleEvents(window, event, nullptr);
        }
        for (unsigned int i = 0; i < 2; ++i) {
            tabs[i]->handleEvents(window, event);
        }
    }
}

void Application::render() {
    window.clear();
    for (unsigned int i = 0; i < 2; ++i) {
        drawTextBox(tabs[i]);
    }
    drawTextBox(inputMusic);

    switch (currentTab) {
        case 1:
            inputMusic->centerShape(window);
            for (unsigned int i = 0; i < 5; ++i) {
                drawTextBox(buttons[i]);
                if (i < 2) {
                    drawTextBox(volButtons[i]);
                }
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

Application::Application(const sf::Font& font_) : font(font_), currentTab(1),
    window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default),
    inputMusic(std::make_unique<TextBoxWrite>(sf::RectangleShape(sf::Vector2f(400, 50)), sf::Color::White, font,
    sf::Text("", font, 24), sf::Color::Black)) {

    window.setFramerateLimit(30);

    EnvironmentSetup::getInstance();
    tabs = Utils::initTabs(font, currentTab);
    buttons = Utils::initButtons();
    volButtons = Utils::initVolButtons();
    display = std::make_unique<PlaylistDisplay>(font);
}

void Application::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

Application::~Application() {
    if (const auto playlistDisplay = dynamic_cast<PlaylistDisplay*>(display.get())) {
        playlistDisplay->savePlaylists();
    }
    std::cout << "App closed." << std::endl;
}


#include "../headers/Application.h"

#include <iostream>

#include "../headers/EnvironmentSetup.h"
#include "../headers/MusicPlayer.h"
#include "../headers/Utility.h"
#include "../headers/PlaylistDisplay.h"

Application::Application(const sf::Font& font_) : font(font_), currentTab(1),
    window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default) {
    window.setFramerateLimit(30);

    EnvironmentSetup::getInstance();

    displayManager.addDisplay(std::make_unique<PlaylistDisplay>(font));

    textBoxManager.addTextBox(std::make_unique<TextBoxWrite>(sf::RectangleShape(sf::Vector2f(400, 50)), sf::Color::White,
        font, sf::Text("", font, 24), sf::Color::Black));
    textBoxManager.addVectorTextBox(Utils::initButtons());
    textBoxManager.addVectorTextBox(Utils::initVolButtons());
    textBoxManager.addVectorTextBox(Utils::initTabs(font, currentTab));
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

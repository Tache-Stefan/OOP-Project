#include "../headers/Application.h"

#include <iostream>

#include "../headers/EnvironmentSetup.h"
#include "../headers/MusicPlayer.h"
#include "../headers/Utility.h"
#include "../headers/PlaylistDisplay.h"
#include "../headers/TextBoxButton.h"

int Application::currentTab = 1;

Application::Application(const sf::Font& font_) : font(font_),
                                                  window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default) {
    window.setFramerateLimit(30);

    EnvironmentSetup::getInstance();
    displayManager.addDisplay(std::make_unique<PlaylistDisplay>(font));
    createUI();
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
        textBox->positionShape(
                sf::Vector2f(1200 * 0.335 + i * 85, 700 * 0.615),
                sf::Vector2f(1200 * 0.335 + 17 + i * 85, 700 * 0.615)
            );
        textBoxManager.addTextBox(std::move(textBox));
    }

    const std::array<std::string, 2> volLabels = {"VOL-", "VOL+"};
    for (unsigned int i = 0; i < volLabels.size(); ++i) {
        const float offsetX = 1200 - (80 + 80 * (1 - i));
        constexpr float offsetY = 700 - 40;

        auto textBox = factory->createVolButton(fontButtons, volLabels[i]);
        textBox->positionShape(
                sf::Vector2f(offsetX, offsetY),
                sf::Vector2f(offsetX + 10, offsetY));
        textBoxManager.addTextBox(std::move(textBox));
    }

    const std::array<std::string, 2> tabLabels = {"Music player", "Playlists"};
    for (unsigned int i = 0; i < tabLabels.size(); ++i) {
        auto textBox = factory->createTab(font, tabLabels[i]);
        if (auto* tab = dynamic_cast<TextBoxTab*>(textBox.get())) {
            tab->setOnClickCallback([i] {
                    currentTab = i + 1;
                });
        }

        textBox->positionShape(
            sf::Vector2f(i * 200, 0),
            sf::Vector2f(20 + i * 230, 12)
            );
        textBoxManager.addTextBox(std::move(textBox));
    }

    auto timer = factory->createTimer(fontButtons);
    timer->positionShape(
        sf::Vector2f(0, 0),
        sf::Vector2f(845, 340));
    textBoxManager.addTextBox(std::move(timer));

    auto volShow = factory->createVolShow(fontButtons);
    volShow->positionShape(
        sf::Vector2f(0, 0),
        sf::Vector2f(1200 * 0.9, 700 * 0.88));
    textBoxManager.addTextBox(std::move(volShow));
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

        textBoxManager.handleEvents(window, event);
        displayManager.handleEvents(window, event);
    }
}

void Application::render() {
    window.clear();
    textBoxManager.draw(window);
    displayManager.draw(window);
    window.display();
}

void Application::run() {
    MusicPlayer::getInstance();
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

Application& Application::getInstance(const sf::Font& font_) {
    static Application app(font_);
    return app;
}

int Application::getCurrentTab() { return currentTab; }

Application::~Application() {
    std::cout << "App closed." << std::endl;
}

#include "../headers/TextBoxConcreteFactory.h"
#include "../headers/TextBoxButton.h"
#include "../headers/TextBoxTab.h"
#include "../headers/TextBoxWrite.h"
#include "../headers/MusicPlayer.h"

std::function<void()> TextBoxConcreteFactory::getButtonCallback(const std::string& label) const {
    if (label == "|<") {
        return [] { MusicPlayer::setSeekToStart(true); };
    }
    if (label == "<") {
        return [] { MusicPlayer::setSkipBack(true); };
    }
    if (label == "| |") {
        return [] {
            if (MusicPlayer::getPaused()) {
                MusicPlayer::setPaused(false);
            } else {
                MusicPlayer::setPaused(true);
            }
        };
    }
    if (label == ">") {
        return [] { MusicPlayer::setSkipForward(true); };
    }
    if (label == ">|") {
        return [] { MusicPlayer::setSeekToEnd(true); };
    }
    return [] {};
}

std::unique_ptr<TextBox> TextBoxConcreteFactory::createButton(const sf::Font &font, const std::string& label) const {
    auto button = std::make_unique<TextBoxButton>(
                sf::RectangleShape(sf::Vector2f(60, 40)),
                label == "| |" ? sf::Color::Red : sf::Color::Green,
                font,
                sf::Text(label, font, 30),
                sf::Color::White
                );
    button->setOnClickCallback(getButtonCallback(label));
    return button;
}

std::unique_ptr<TextBox> TextBoxConcreteFactory::createVolButton(const sf::Font &font, const std::string &label) const {
    auto volButton = std::make_unique<TextBoxButton>(
        sf::RectangleShape(sf::Vector2f(80, 40)),
        label == "VOL-" ? sf::Color::Red : sf::Color::Green,
        font,
        sf::Text(label, font, 28),
        sf::Color::White
        );
    volButton->setOnClickCallback(label == "VOL-" ?
            [] { MusicPlayer::decreaseVolume(); } :
            [] { MusicPlayer::increaseVolume(); }
            );
    return volButton;
}

std::unique_ptr<TextBox> TextBoxConcreteFactory::createTab(const sf::Font &font, const std::string &label) const {
    auto tab = std::make_unique<TextBoxTab>(
        sf::RectangleShape(sf::Vector2f(200, 50)),
        sf::Color::Green,
        font,
        sf::Text(label, font, 20),
        sf::Color::Black);
    return tab;
}

std::unique_ptr<TextBox> TextBoxConcreteFactory::createWrite(const sf::Font &font) const {
    auto write = std::make_unique<TextBoxWrite>(
        sf::RectangleShape(sf::Vector2f(400, 50)),
        sf::Color::White,
        font,
        sf::Text("", font, 24),
        sf::Color::Black);
    return write;
}

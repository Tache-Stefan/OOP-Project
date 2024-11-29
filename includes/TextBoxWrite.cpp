#include "TextBoxWrite.h"

#include <iostream>

#include "API.h"
#include "EnvironmentSetup.h"

TextBoxWrite::TextBoxWrite(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                 const sf::Color& textColor) : TextBox(box_, boxColor, font_, text_, textColor) {}

bool TextBoxWrite::containsClick(const sf::Vector2f& mousePosition) {
    if (box.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        isActive = true;
        return true;
    }
    isActive = false;
    return false;
}

bool TextBoxWrite::getActive() const { return isActive; }

void TextBoxWrite::handleEvents(sf::RenderWindow& window, const sf::Event& event, std::atomic<bool>& stopPlayback,
                                std::atomic<bool>& isMusicPlaying, std::string& userInput) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            containsClick(mousePos);
        }
    }

    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8 && !userInput.empty()) {
                userInput.pop_back();
            } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                userInput += static_cast<char>(event.text.unicode);
            }
        }
        setText(userInput);
    }

    if (event.type == sf::Event::Resized) {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        centerShape(window);
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            userInput.clear();
            stopPlayback.store(false);
            searchAndPlay(stopPlayback, isMusicPlaying);
        }
        if (!isActive && isMusicPlaying && event.key.code == sf::Keyboard::S) {
            stopPlayback.store(true);
            std::cout << "Playback stopped!" << std::endl;
        }
    }
}

void TextBoxWrite::searchAndPlay(std::atomic<bool>& stopPlayback, std::atomic<bool>& isMusicPlaying) {
    const std::shared_ptr<Song> song = API::searchSpotifySong(EnvironmentSetup::getAccessToken(), text.getString());
    text.setString("");
    song->play(EnvironmentSetup::getYoutubeAPI(), stopPlayback, isMusicPlaying);
}

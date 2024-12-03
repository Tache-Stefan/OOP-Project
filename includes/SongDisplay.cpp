#include "SongDisplay.h"

#include <iostream>

#include "API.h"
#include "EnvironmentSetup.h"
#include "TextBoxPlaylist.h"

unsigned int SongDisplay::currentIndex = 0;

SongDisplay::SongDisplay(const sf::Font &font_, const std::vector<std::shared_ptr<Song>> &songs_) :
                         songs(songs_), font(font_), scrollSpeed(40.f), verticalOffset(0.f), visibleCount(10), itemHeight(40) {}

void SongDisplay::draw(sf::RenderWindow& window) {

    for (unsigned int i = 0; i < visibleCount; ++i) {
        currentIndex = i + verticalOffset / itemHeight;
        if (currentIndex >= songs.size()) break;

        sf::RectangleShape textButton(sf::Vector2f(200, 40));
        textButton.setPosition(500.f, 200.f + (i * itemHeight));
        sf::Text text;
        text.setFont(font);
        text.setString(songs[currentIndex]->getTitle());
        text.setCharacterSize(24);
        text.setPosition(510.f, 205.f + (i * itemHeight));

        TextBoxPlaylist playlistButton(textButton, sf::Color(144, 213, 255), font, text, sf::Color::Black);
        playlistButton.draw(window);

        sf::RectangleShape addBox(sf::Vector2f(300, 50));
    }
}

void SongDisplay::scrollUp() {
    if (verticalOffset > 0) {
        verticalOffset -= scrollSpeed;
    }
}

void SongDisplay::scrollDown() {
    const int maxScroll = (songs.size() > visibleCount) ? (songs.size() - visibleCount) * itemHeight : 0;

    if (verticalOffset < maxScroll) {
        verticalOffset += scrollSpeed;
    }
    if (verticalOffset > maxScroll) {
        verticalOffset = maxScroll;
    }
}

void SongDisplay::scrollWithMouse(const float delta) {
    if (delta < 0) {
        scrollDown();
    } else if (delta > 0) {
        scrollUp();
    }
}

void SongDisplay::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (mousePos.y >= 200 && mousePos.y <= 600 && mousePos.x >= 500 && mousePos.x <= 700) {
            scrollWithMouse(event.mouseWheelScroll.delta);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        for (unsigned int i = 0; i < visibleCount; ++i) {

            const unsigned int songIndex = i + verticalOffset / itemHeight;
            if (songIndex >= songs.size()) break;

            const float boxTop = 200.f + (i * itemHeight);
            const float boxBottom = boxTop + itemHeight;

            if (mousePos.y >= boxTop && mousePos.y <= boxBottom && mousePos.x >= 500 && mousePos.x <= 700) {
                std::cout << "Clicked on song: " << songs[songIndex]->getTitle() << std::endl;
                break;
            }
        }
    }

    if (event.type == sf::Event::Resized) {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
    }
}

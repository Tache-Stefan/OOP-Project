#include "SongDisplay.h"

#include <iostream>

#include "API.h"
#include "EnvironmentSetup.h"
#include "TextBoxPlaylist.h"

unsigned int SongDisplay::currentIndex = 0;

SongDisplay::SongDisplay(const sf::Font &font_) :
    font(font_),
    inputBox(TextBoxWrite(sf::RectangleShape(sf::Vector2f(300.f, 50.f)), sf::Color::White, font,
   sf::Text("", font, 24), sf::Color::Black)),
    scrollSpeed(40.f), verticalOffset(0.f), visibleCount(10), itemHeight(40) {
    inputBox.positionShape(
            sf::Vector2f(1200 * 0.7f, 700 * 0.2f),
            sf::Vector2f(1200 * 0.71f, 700 * 0.21f)
            );
    inputText.setFont(font);
    inputText.setString("Enter a song to add to the playlist");
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(1200 * 0.695f, 700 * 0.16f);
}

SongDisplay::SongDisplay(const sf::Font &font_, const std::vector<std::shared_ptr<Song>> &songs_) :
    songs(songs_), font(font_),
    inputBox(TextBoxWrite(sf::RectangleShape(sf::Vector2f(300.f, 50.f)), sf::Color::White, font,
   sf::Text("", font, 24), sf::Color::Black)),
    scrollSpeed(40.f), verticalOffset(0.f), visibleCount(10), itemHeight(40) {
    inputBox.positionShape(
            sf::Vector2f(1200 * 0.7f, 700 * 0.2f),
            sf::Vector2f(1200 * 0.71f, 700 * 0.21f)
            );
    inputText.setFont(font);
    inputText.setString("Enter a song to add to the playlist");
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(1200 * 0.695f, 700 * 0.16f);
}

void SongDisplay::setSongs(const std::vector<std::shared_ptr<Song>>& songs_) {songs = songs_;}

void SongDisplay::draw(sf::RenderWindow& window) {
    sf::Text songsText("Songs", font, 24);
    songsText.setFillColor(sf::Color::White);
    songsText.setPosition(550.f, 160.f);
    window.draw(songsText);

    for (unsigned int i = 0; i < visibleCount; ++i) {
        currentIndex = i + verticalOffset / itemHeight;
        if (currentIndex >= songs.size()) break;

        sf::RectangleShape textButton(sf::Vector2f(200, 40));
        textButton.setPosition(500.f, 200.f + (i * itemHeight));
        sf::Text text(songs[currentIndex]->getTitle(), font, 24);
        text.setPosition(510.f, 205.f + (i * itemHeight));

        TextBoxPlaylist playlistButton(textButton, sf::Color(144, 213, 255), font, text, sf::Color::Black);
        playlistButton.draw(window);
    }
    window.draw(inputText);
    inputBox.draw(window);
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

void SongDisplay::handleEvents(sf::RenderWindow& window, const sf::Event& event, Playlist& playlist) {
    inputBox.handleEventsPlaylist(window, event, playlist);

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
        const float windowWidth = static_cast<float>(event.size.width);
        const float windowHeight = static_cast<float>(event.size.height);

        inputBox.positionShape(
            sf::Vector2f(windowWidth * 0.7f, windowHeight * 0.2f),
            sf::Vector2f(windowWidth * 0.71f, windowHeight * 0.21f)
        );
        inputText.setPosition(windowWidth * 0.695f, windowHeight * 0.16f);
    }
}

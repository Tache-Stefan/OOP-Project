#include "SongDisplay.h"

#include <iostream>

#include "API.h"
#include "EnvironmentSetup.h"
#include "Exceptions.h"
#include "TextBoxDelete.h"
#include "TextBoxPlaylist.h"

unsigned int SongDisplay::currentIndex = 0;

SongDisplay::SongDisplay(const sf::Font &font_) :
    font(font_),
    inputBox(TextBoxWrite(sf::RectangleShape(sf::Vector2f(300.f, 50.f)), sf::Color::White, font,
   sf::Text("", font, 24), sf::Color::Black)),
    songsText(sf::Text("Songs", font, 24)),
    scrollSpeed(40.f), verticalOffset(0.f), visibleCount(8), itemHeight(40), windowWidth(1200), windowHeight(700) {

    inputBox.positionShape(
            sf::Vector2f(windowWidth * 0.73f, windowHeight * 0.2f),
            sf::Vector2f(windowWidth * 0.74f, windowHeight * 0.21f)
            );
    inputText.setFont(font);
    inputText.setString("Enter a song to add to the playlist");
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(windowWidth * 0.725f, windowHeight * 0.16f);

    songsText.setFillColor(sf::Color::White);
    songsText.setPosition(windowWidth * 0.5f + 90, windowHeight * 0.16f);

    for (unsigned int i = 0; i < 8; ++i) {
        textsRects[i] = sf::RectangleShape(sf::Vector2f(200, 40));
        texts[i] = sf::Text("", font, 24);
        deleteRects[i] = sf::RectangleShape(sf::Vector2f(60, 39));
    }
}

void SongDisplay::setSongs(const std::vector<std::shared_ptr<Song>>& songs_) {songs = songs_;}

std::vector<std::shared_ptr<Song>> SongDisplay::getSongs() const {return songs;}

void SongDisplay::draw(sf::RenderWindow& window) {
    window.draw(songsText);

    for (unsigned int i = 0; i < visibleCount; ++i) {
        currentIndex = i + verticalOffset / itemHeight;
        if (currentIndex >= songs.size()) break;

        textsRects[i].setPosition(windowWidth * 0.5f, windowHeight * 0.215f + (i * itemHeight));
        texts[i].setPosition(windowWidth * 0.5f + 10, windowHeight * 0.215f + 5 + (i * itemHeight));
        texts[i].setString(songs[currentIndex]->getTitle());

        TextBoxPlaylist playlistButton(textsRects[i], sf::Color(144, 213, 255), font, texts[i], sf::Color::Black);
        playlistButton.draw(window);

        deleteRects[i].setPosition(windowWidth * 0.5f + 200.f, windowHeight * 0.215f + (i * itemHeight));
        sf::Text deleteText;
        deleteText.setPosition(windowWidth * 0.5f + 217.f, windowHeight * 0.215f + (i * itemHeight));
        TextBoxDelete deleteButton(deleteRects[i], font, deleteText);
        deleteButton.draw(window);
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
    try {
        inputBox.handleEventsSongDisplay(window, event, playlist);
    } catch (const SearchException& e) {
        std::cerr << e.what() << std::endl;
    }

    const float boxLeft = windowWidth * 0.5f;
    const float boxRight = windowWidth * 0.5f + 200.f;

    if (event.type == sf::Event::MouseWheelScrolled) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (mousePos.y >= windowHeight * 0.214f && mousePos.y <= windowHeight * 0.214f + visibleCount * 40 &&
            mousePos.x >= boxLeft && mousePos.x <= boxRight) {
            scrollWithMouse(event.mouseWheelScroll.delta);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        for (unsigned int i = 0; i < visibleCount; ++i) {

            const unsigned int songIndex = i + verticalOffset / itemHeight;
            if (songIndex >= songs.size()) break;

            const float boxTop = windowHeight * 0.214f + (i * itemHeight);
            const float boxBottom = boxTop + itemHeight;

            if (mousePos.y >= boxTop && mousePos.y <= boxBottom && mousePos.x >= boxLeft && mousePos.x <= boxRight) {
                std::cout << "Clicked on song: " << songs[songIndex]->getTitle() << std::endl;
                break;
            }
            if (mousePos.y >= boxTop && mousePos.y <= boxBottom && mousePos.x >= boxRight && mousePos.x <= boxRight + 60) {
                TextBoxDelete::clickedSong(songs, songIndex);
                break;
            }
        }
    }

    if (event.type == sf::Event::Resized) {
        windowWidth = static_cast<float>(event.size.width);
        windowHeight = static_cast<float>(event.size.height);

        inputBox.positionShape(
            sf::Vector2f(windowWidth * 0.73f, windowHeight * 0.2f),
            sf::Vector2f(windowWidth * 0.74f, windowHeight * 0.21f)
        );
        inputText.setPosition(windowWidth * 0.725f, windowHeight * 0.16f);

        songsText.setPosition(windowWidth * 0.5f + 90, windowHeight * 0.16f);
    }
}

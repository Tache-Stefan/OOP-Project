#include "PlaylistDisplay.h"

#include <fstream>
#include <iostream>

#include "API.h"
#include "Exceptions.h"
#include "TextBoxDelete.h"
#include "TextBoxPlaylist.h"

unsigned int PlaylistDisplay::currentIndex = 0;
int PlaylistDisplay::change = -1;

PlaylistDisplay::PlaylistDisplay(const sf::Font &font_) : font(font_), songDisplay(font_),
    inputBox(TextBoxWrite(sf::RectangleShape(sf::Vector2f(300.f, 50.f)), sf::Color::White, font,
    sf::Text("", font, 24), sf::Color::Black)),
    playlistsText(sf::Text ("Playlists", font, 24)),
    scrollSpeed(40.f), verticalOffset(0.f), visibleCount(8), itemHeight(40) {

    inputBox.positionShape(
            sf::Vector2f(1200 * 0.23f, 700 * 0.2f),
            sf::Vector2f(1200 * 0.24f, 700 * 0.21f)
            );
    inputText.setFont(font);
    inputText.setString("Enter the name of a playlist to add");
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(1200 * 0.225f, 700 * 0.16f);

    playlistsText.setFillColor(sf::Color::White);
    playlistsText.setPosition(60.f, 160.f);

    for (unsigned int i = 0; i < 8; ++i) {
        textsRects[i] = sf::RectangleShape(sf::Vector2f(200, 40));
        texts[i] = sf::Text("", font, 24);
        deleteRects[i] = sf::RectangleShape(sf::Vector2f(60, 40));
    }

    loadPlaylists();
}

void PlaylistDisplay::draw(sf::RenderWindow& window) {
    window.draw(playlistsText);
    window.draw(inputText);
    inputBox.draw(window);

    for (unsigned int i = 0; i < visibleCount; ++i) {
        currentIndex = i + verticalOffset / itemHeight;
        if (currentIndex >= playlists.size()) break;

        //sf::RectangleShape textButton(sf::Vector2f(200, 40));
        textsRects[i].setPosition(0.f, 200.f + (i * itemHeight));
        //sf::Text text(playlists[currentIndex].getTitle(), font, 24);
        texts[i].setString(playlists[currentIndex].getTitle());
        texts[i].setPosition(10.f, 205.f + (i * itemHeight));

        TextBoxPlaylist playlistButton(textsRects[i], sf::Color(144, 213, 255), font, texts[i], sf::Color::Black);
        playlistButton.draw(window);

        //sf::RectangleShape deleteRect(sf::Vector2f(60, 40));
        deleteRects[i].setPosition(200.f, 200.f + (i * itemHeight));
        sf::Text deleteText;
        deleteText.setPosition(217.f, 200.f + (i * itemHeight));
        TextBoxDelete deleteButton(deleteRects[i], font, deleteText);
        deleteButton.draw(window);

        if (menuActive) {
            songDisplay.draw(window);
        }
    }
}

void PlaylistDisplay::scrollUp() {
    if (verticalOffset > 0) {
        verticalOffset -= scrollSpeed;
    }
}

void PlaylistDisplay::scrollDown() {
    const int maxScroll = (playlists.size() > visibleCount) ? (playlists.size() - visibleCount) * itemHeight : 0;

    if (verticalOffset < maxScroll) {
        verticalOffset += scrollSpeed;
    }
    if (verticalOffset > maxScroll) {
        verticalOffset = maxScroll;
    }
}

void PlaylistDisplay::scrollWithMouse(const float delta) {
    if (delta < 0) {
        scrollDown();
    } else if (delta > 0) {
        scrollUp();
    }
}

void PlaylistDisplay::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    songDisplay.handleEvents(window, event, playlists[currentPlaylist]);
    if (change == 1) {
        songDisplay.setSongs(playlists[currentPlaylist].getSongs());
        change = -1;
    }
    if (change == 2) {
        playlists[currentPlaylist].setSongs(songDisplay.getSongs());
        change = -1;
    }

    try {
        inputBox.handleEventsPlaylistDisplay(window, event, playlists);
    } catch (const PlaylistException& e) {
        std::cerr << e.what() << std::endl;
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (mousePos.y >= 200 && mousePos.y <= 200 + visibleCount * 40 && mousePos.x >= 0 && mousePos.x <= 200) {
            scrollWithMouse(event.mouseWheelScroll.delta);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        for (unsigned int i = 0; i < visibleCount; ++i) {

            const unsigned int playlistIndex = i + verticalOffset / itemHeight;
            if (playlistIndex >= playlists.size()) break;

            const float boxTop = 200.f + (i * itemHeight);
            const float boxBottom = boxTop + itemHeight;

            if (mousePos.y >= boxTop && mousePos.y <= boxBottom && mousePos.x >= 0 && mousePos.x <= 200) {
                std::cout << "Clicked on playlist: " << playlists[playlistIndex].getTitle() << std::endl;
                if (menuActive == false) {
                    currentPlaylist = playlistIndex;
                    songDisplay.setSongs(playlists[currentPlaylist].getSongs());
                    menuActive = true;
                    break;
                }
                currentPlaylist = -1;
                menuActive = false;
                break;
            }
            if (mousePos.y >= boxTop && mousePos.y <= boxBottom && mousePos.x >= 200 && mousePos.x <= 260) {
                menuActive = false;
                TextBoxDelete::clickedPlaylist(playlists, playlistIndex);
                break;
            }
        }
    }

    if (event.type == sf::Event::Resized) {
        const float windowWidth = static_cast<float>(event.size.width);
        const float windowHeight = static_cast<float>(event.size.height);

        inputBox.positionShape(
            sf::Vector2f(windowWidth * 0.23f, windowHeight * 0.2f),
            sf::Vector2f(windowWidth * 0.24f, windowHeight * 0.21f)
            );
        inputText.setPosition(windowWidth * 0.225f, windowHeight * 0.16f);
    }
}

void PlaylistDisplay::savePlaylists() {
    std::ofstream file("playlists.json", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Could not open playlists.json" << std::endl;
    }

    nlohmann::json j = playlists;
    file << j.dump(4);
    file.close();
}

void PlaylistDisplay::loadPlaylists() {
    playlists.clear();

    std::ifstream file("playlists.json");
    if (!file.is_open()) {
        std::cerr << "Could not open playlists.json" << std::endl;
    }

    nlohmann::json j;
    file >> j;
    playlists = j.get<std::vector<Playlist>>();
    file.close();
}

void PlaylistDisplay::needChangeAddSong() {change = 1;}

void PlaylistDisplay::needChangeRemoveSong() {change = 2;}

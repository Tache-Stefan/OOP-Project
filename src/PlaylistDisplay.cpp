#include "../headers/PlaylistDisplay.h"

#include <fstream>
#include <iostream>
#include <set>

#include "../headers/API.h"
#include "../headers/Exceptions.h"
#include "../headers/TextBoxDelete.h"
#include "../headers/TextBoxPlaylist.h"

unsigned int PlaylistDisplay::currentIndex = 0;
int PlaylistDisplay::change = -1;

void PlaylistDisplay::setMaxScroll(int& maxScroll) {
    maxScroll = (playlists.size() > visibleCount) ? (playlists.size() - visibleCount) * itemHeight : 0;
}

PlaylistDisplay::PlaylistDisplay(const sf::Font &font_) : Display(font_), songDisplay(font_),
    playlistsText(sf::Text ("Playlists", font, 24)) {

    inputBox.positionShape(
            sf::Vector2f(windowWidth * 0.23f, windowHeight * 0.2f),
            sf::Vector2f(windowWidth * 0.24f, windowHeight * 0.21f)
            );
    inputText.setFont(font);
    inputText.setString("Enter the name of a playlist to add");
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(windowWidth * 0.225f, windowHeight * 0.16f);

    playlistsText.setFillColor(sf::Color::White);
    playlistsText.setPosition(60.f, 240.f);

    for (unsigned int i = 0; i < 8; ++i) {
        playRects[i] = sf::RectangleShape(sf::Vector2f(80, 40));
        playTexts[i] = sf::Text("Play", font, 24);
        shuffleRects[i] = sf::RectangleShape(sf::Vector2f(110, 40));
        shuffleTexts[i] = sf::Text("Shuffle", font, 24);
    }

    try {
        loadPlaylists();
    }
    catch (const FileException &e) {
        std::cout << e.what() << std::endl;
    }
}

void PlaylistDisplay::draw(sf::RenderWindow& window) {
    window.draw(playlistsText);
    window.draw(inputText);
    inputBox.draw(window);

    for (unsigned int i = 0; i < visibleCount; ++i) {
        currentIndex = i + verticalOffset / itemHeight;
        if (currentIndex >= playlists.size()) break;

        textsRects[i].setPosition(0.f, 280.f + (i * itemHeight));
        texts[i].setString(playlists[currentIndex].getTitle());
        texts[i].setPosition(10.f, 285.f + (i * itemHeight));

        TextBoxPlaylist playlistButton(textsRects[i], sf::Color(144, 213, 255), font, texts[i], sf::Color::Black);
        playlistButton.draw(window);

        playRects[i].setPosition(260.f, 280.f + (i * itemHeight));
        playTexts[i].setPosition(270.f, 285.f + (i * itemHeight));
        TextBoxPlaylist playButton(playRects[i], sf::Color::Green, font, playTexts[i], sf::Color::Black);
        playButton.draw(window);

        shuffleRects[i].setPosition(340.f, 280.f + (i * itemHeight));
        shuffleTexts[i].setPosition(350.f, 285.f + (i * itemHeight));
        TextBoxPlaylist shuffleButton(shuffleRects[i], sf::Color::Green, font, shuffleTexts[i], sf::Color::Black);
        shuffleButton.draw(window);

        deleteRects[i].setPosition(200.f, 280.f + (i * itemHeight));
        sf::Text deleteText;
        deleteText.setPosition(217.f, 280.f + (i * itemHeight));
        TextBoxDelete deleteButton(deleteRects[i], font, deleteText);
        deleteButton.draw(window);

        if (menuActive) {
            songDisplay.draw(window);
        }
    }
}

void PlaylistDisplay::handleEvents(sf::RenderWindow& window, const sf::Event& event, Playlist* playlist) {
    (void)playlist;
    if (menuActive) {
        songDisplay.handleEvents(window, event, &playlists[currentPlaylist]);
    }
    if (change == 1 || change == 3) {
        songDisplay.setSongs(playlists[currentPlaylist].getSongs());
        change = -1;
    }
    if (change == 2) {
        playlists[currentPlaylist].setSongs(songDisplay.getSongs());
        change = -1;
    }

    inputBox.handleEventsPlaylistDisplay(window, event, playlists);

    if (event.type == sf::Event::MouseWheelScrolled) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (mousePos.y >= 280 && mousePos.y <= 280 + visibleCount * 40 && mousePos.x >= 0 && mousePos.x <= 200) {
            scrollWithMouse(event.mouseWheelScroll.delta);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        for (unsigned int i = 0; i < visibleCount; ++i) {

            const unsigned int playlistIndex = i + verticalOffset / itemHeight;
            if (playlistIndex >= playlists.size()) break;

            const float boxTop = 280.f + (i * itemHeight);
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
            if (mousePos.y >= boxTop && mousePos.y <= boxBottom && mousePos.x > 200 && mousePos.x <= 260) {
                menuActive = false;
                TextBoxDelete::clickedItem(playlists, playlistIndex);
                break;
            }
            if (mousePos.y >= boxTop && mousePos.y <= boxBottom && mousePos.x > 260 && mousePos.x <= 340) {
                playlists[playlistIndex].play();
            }
            if (mousePos.y >= boxTop && mousePos.y <= boxBottom && mousePos.x > 340 && mousePos.x <= 450) {
                playlists[playlistIndex].shuffle();
                change = 3;
            }
        }
    }

    if (event.type == sf::Event::Resized) {
        windowWidth = static_cast<float>(event.size.width);
        windowHeight = static_cast<float>(event.size.height);

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
        throw FileException("playlists.json");
    }

    const nlohmann::json j = playlists;
    file << j.dump(4);
    file.close();
}

void PlaylistDisplay::loadPlaylists() {
    playlists.clear();

    std::ifstream file("playlists.json");
    if (!file.is_open()) {
        throw FileException("playlists.json");
    }

    nlohmann::json j;
    file >> j;
    playlists = j.get<std::vector<Playlist>>();
    file.close();
}

void PlaylistDisplay::needChangeAddSong() {change = 1;}

void PlaylistDisplay::needChangeRemoveSong() {change = 2;}

PlaylistDisplay* PlaylistDisplay::clone() const {
    return new PlaylistDisplay(*this);
}

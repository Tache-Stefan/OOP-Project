#include "PlaylistDisplay.h"

#include <fstream>
#include <iostream>

#include "API.h"
#include "TextBoxPlaylist.h"

unsigned int PlaylistDisplay::currentIndex = 0;
bool PlaylistDisplay::change = false;

PlaylistDisplay::PlaylistDisplay(const sf::Font &font_) : font(font_), songDisplay(font), scrollSpeed(40.f), verticalOffset(0.f), visibleCount(10),
                                                          itemHeight(40) {
    /*playlists.emplace_back(Playlist("test1"));
    playlists.emplace_back(Playlist("test2"));
    playlists.emplace_back(Playlist("test3"));
    playlists.emplace_back(Playlist("test4"));
    playlists.emplace_back(Playlist("test5"));
    playlists.emplace_back(Playlist("test6"));
    playlists.emplace_back(Playlist("test7"));
    playlists.emplace_back(Playlist("test8"));
    playlists.emplace_back(Playlist("test9"));
    playlists.emplace_back(Playlist("test10"));
    playlists.emplace_back(Playlist("test11"));
    playlists.emplace_back(Playlist("test12"));
    savePlaylists();*/
    loadPlaylists();
}

void PlaylistDisplay::draw(sf::RenderWindow& window) {
    sf::Text songsText("Playlists", font, 24);
    songsText.setFillColor(sf::Color::White);
    songsText.setPosition(40.f, 160.f);
    window.draw(songsText);

    for (unsigned int i = 0; i < visibleCount; ++i) {
        currentIndex = i + verticalOffset / itemHeight;
        if (currentIndex >= playlists.size()) break;

        sf::RectangleShape textButton(sf::Vector2f(200, 40));
        textButton.setPosition(0.f, 200.f + (i * itemHeight));
        sf::Text text(playlists[currentIndex].getTitle(), font, 24);
        text.setPosition(10.f, 205.f + (i * itemHeight));

        TextBoxPlaylist playlistButton(textButton, sf::Color(144, 213, 255), font, text, sf::Color::Black);
        playlistButton.draw(window);

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
    if (change) {
        songDisplay.setSongs(playlists[currentPlaylist].getSongs());
        change = false;
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (mousePos.y >= 200 && mousePos.y <= 600 && mousePos.x >= 0 && mousePos.x <= 200) {
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
        }
    }

    if (event.type == sf::Event::Resized) {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
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

void PlaylistDisplay::needChange() {change = true;}

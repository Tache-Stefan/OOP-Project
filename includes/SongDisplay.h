#pragma once

#include <array>

#include <SFML/Graphics.hpp>
#include "Song.h"
#include "TextBoxWrite.h"

class SongDisplay {
private:
    std::vector<std::shared_ptr<Song>> songs;
    sf::Font font;
    TextBoxWrite inputBox;
    sf::Text inputText;
    sf::Text songsText;
    std::array<sf::RectangleShape, 8> textsRects;
    std::array<sf::Text, 8> texts;
    std::array<sf::RectangleShape, 8> deleteRects;
    float scrollSpeed;
    float verticalOffset;
    unsigned int visibleCount;
    int itemHeight;
    static unsigned int currentIndex;
    float windowWidth;
    float windowHeight;
public:
    explicit SongDisplay(const sf::Font& font_);
    void setSongs(const std::vector<std::shared_ptr<Song>>& songs_);
    std::vector<std::shared_ptr<Song>> getSongs() const;
    void draw(sf::RenderWindow &window);
    void scrollUp();
    void scrollDown();
    void scrollWithMouse(float delta);
    void handleEvents(sf::RenderWindow &window, const sf::Event& event, Playlist& playlist);
};

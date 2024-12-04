#pragma once

#include <SFML/Graphics.hpp>
#include "Song.h"
#include "TextBoxWrite.h"

class SongDisplay {
private:
    std::vector<std::shared_ptr<Song>> songs;
    sf::Font font;
    TextBoxWrite inputBox;
    sf::Text inputText;
    float scrollSpeed;
    float verticalOffset;
    unsigned int visibleCount;
    int itemHeight;
    static unsigned int currentIndex;
public:
    explicit SongDisplay(const sf::Font& font_);
    SongDisplay(const sf::Font &font_, const std::vector<std::shared_ptr<Song>> &songs_);
    void setSongs(const std::vector<std::shared_ptr<Song>>& songs_);
    void draw(sf::RenderWindow &window);
    void scrollUp();
    void scrollDown();
    void scrollWithMouse(float delta);
    void handleEvents(sf::RenderWindow &window, const sf::Event& event, Playlist& playlist);
};

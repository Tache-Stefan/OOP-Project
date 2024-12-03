#pragma once

#include <SFML/Graphics.hpp>
#include "Song.h"

class SongDisplay {
private:
    std::vector<std::shared_ptr<Song>> songs;
    sf::Font font;
    float scrollSpeed;
    float verticalOffset;
    unsigned int visibleCount;
    int itemHeight;
    static unsigned int currentIndex;
public:
    explicit SongDisplay(const sf::Font &font_, const std::vector<std::shared_ptr<Song>> &songs_);
    void draw(sf::RenderWindow &window);
    void scrollUp();
    void scrollDown();
    void scrollWithMouse(float delta);
    void handleEvents(sf::RenderWindow &window, const sf::Event &event);
};

#pragma once
#include "TextBox.h"

#include <atomic>
#include <SFML/Graphics.hpp>

#include "Playlist.h"

class TextBoxWrite : public TextBox {
private:
    bool isActive = false;
    std::string userInput = "";
public:
    TextBoxWrite();
    TextBoxWrite(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_, const sf::Color& textColor);
    bool containsClick(const sf::Vector2f& mousePosition);
    void handleEventsMusic(sf::RenderWindow& window, const sf::Event& event, std::atomic<bool>& stopPlayback,
                      std::atomic<bool>& isMusicPlaying);
    void handleEventsPlaylist(sf::RenderWindow& window, const sf::Event& event, Playlist& playlist);
    void searchAndPlay(std::atomic<bool>& stopPlayback, std::atomic<bool>& isMusicPlaying);
    void draw(sf::RenderWindow& window) const override;
    void draw(sf::RenderWindow& window, std::atomic<bool>& isMusicPlaying) const;
    bool getActive() const;
    TextBox* clone() const override;
};

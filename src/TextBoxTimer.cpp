#include "../headers/TextBoxTimer.h"

#include <iostream>

#include "../headers/MusicPlayer.h"

TextBoxTimer::TextBoxTimer(const sf::RectangleShape &box_, const sf::Color &boxColor, const sf::Font &font_,
                           const sf::Text &text_, const sf::Color &textColor) :
                           TextBox(box_, boxColor, font_, text_, textColor), isPlaying(false), elapsedTime(sf::Time::Zero) {}

void TextBoxTimer::setPlaying(const bool &playing) { isPlaying = playing; }

std::string TextBoxTimer::formatTime(const sf::Time& time) const {
    const int minutes = static_cast<int>(time.asSeconds()) / 60;
    const int seconds = static_cast<int>(time.asSeconds()) % 60;
    return (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
}

void TextBoxTimer::updateText() {
    updateTime();
    const std::string elapsedStr = formatTime(elapsedTime);
    const std::string totalStr = formatTime(totalDuration);
    text.setString(elapsedStr + " / " + totalStr);
}

void TextBoxTimer::updateTime() {
    elapsedTime = MusicPlayer::getElapsedTime();
    totalDuration = MusicPlayer::getTotalTime();
}

void TextBoxTimer::handleEvents(sf::RenderWindow&, const sf::Event&) {}

void TextBoxTimer::extraDraw(sf::RenderWindow&) {
    updateText();
}

TextBoxTimer* TextBoxTimer::clone() const {
    return new TextBoxTimer(*this);
}

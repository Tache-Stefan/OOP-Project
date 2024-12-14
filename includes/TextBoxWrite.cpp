#include "TextBoxWrite.h"

#include "API.h"
#include "EnvironmentSetup.h"
#include "Exceptions.h"
#include "MusicPlayer.h"
#include "PlaylistDisplay.h"

void TextBoxWrite::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        containsClick(mousePos);
    }

    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8 && !userInput.empty()) {
                userInput.pop_back();
            } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                userInput += static_cast<char>(event.text.unicode);
            }
        }
        setText(userInput);
    }

    if (event.type == sf::Event::Resized) {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        centerShape(window);
    }
}

TextBoxWrite::TextBoxWrite() = default;

TextBoxWrite::TextBoxWrite(const sf::RectangleShape& box_, const sf::Color& boxColor, const sf::Font& font_, const sf::Text& text_,
                           const sf::Color& textColor) : TextBox(box_, boxColor, font_, text_, textColor) {}

bool TextBoxWrite::containsClick(const sf::Vector2f& mousePosition) {
    if (box.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        isActive = true;
        return true;
    }
    isActive = false;
    return false;
}

void TextBoxWrite::handleEventsMusic(sf::RenderWindow& window, const sf::Event& event) {
    handleEvents(window, event);

    if (isActive && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        if (userInput.empty()) {
            throw SearchException(userInput);
        }
        MusicPlayer::setLoadingMusic(true);
        const std::shared_ptr<Song> song = API::searchSpotifySong(EnvironmentSetup::getAccessToken(), userInput);
        userInput.clear();
        MusicPlayer::setStopPlayback(true);
        MusicPlayer::setPlaylistPlaying(false);
        song->play();
    }
}

void TextBoxWrite::handleEventsSongDisplay(sf::RenderWindow& window, const sf::Event& event, Playlist* playlist) {
    handleEvents(window, event);

    if (isActive && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        if (userInput.empty()) {
            throw SearchException(userInput);
        }
        const std::shared_ptr<Song> song = API::searchSpotifySong(EnvironmentSetup::getAccessToken(), userInput);
        userInput.clear();
        playlist->addSong(song);
        PlaylistDisplay::needChangeAddSong();
    }
}

void TextBoxWrite::handleEventsPlaylistDisplay(sf::RenderWindow& window, const sf::Event& event, std::vector<Playlist>& playlists) {
    handleEvents(window, event);

    if (isActive && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        for (const auto& playlist : playlists) {
            if (playlist.getTitle() == userInput) {
                throw PlaylistException(userInput);
            }
        }
        playlists.emplace_back(userInput);
        userInput.clear();
    }
}

void TextBoxWrite::draw(sf::RenderWindow& window) const { TextBox::draw(window); }

void TextBoxWrite::drawSearch(sf::RenderWindow& window) const {
    TextBox::draw(window);
    sf::Text query("Enter the song name", font, 24);
    query.setFillColor(sf::Color::White);
    query.setPosition(box.getPosition().x + 60, box.getPosition().y - 50);
    window.draw(query);
    if (MusicPlayer::getLoadingMusic()) {
        sf::Text loading("Loading music...", font, 24);
        loading.setFillColor(sf::Color::White);
        loading.setPosition(box.getPosition().x + 90, box.getPosition().y + 65);
        window.draw(loading);
    }
    if (MusicPlayer::getIsMusicPlaying()) {
        sf::Text playing("Playing song - " + *MusicPlayer::getCurrentSong(), font, 24);
        playing.setFillColor(sf::Color::White);
        playing.setPosition(box.getPosition().x, box.getPosition().y + 65);
        window.draw(playing);
    }
}

bool TextBoxWrite::getActive() const { return isActive; }

TextBoxWrite* TextBoxWrite::clone() const {
    return new TextBoxWrite(*this);
}

TextBoxWrite& TextBoxWrite::operator=(const TextBoxWrite& other) {
    TextBoxWrite* temp = other.clone();
    swap(*this, *temp);
    delete temp;
    return *this;
}

void swap(TextBoxWrite& t1, TextBoxWrite& t2) noexcept {
    using std::swap;
    swap(t1.font, t2.font);
    swap(t1.box, t2.box);
    swap(t1.text, t2.text);
    swap(t1.isActive, t2.isActive);
    swap(t1.userInput, t2.userInput);
}

TextBoxWrite::TextBoxWrite(const TextBoxWrite& other) : TextBox(other), isActive(other.isActive), userInput(other.userInput) {}

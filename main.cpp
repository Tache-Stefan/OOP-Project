#include <iostream>
#include <string>

#include "includes/API.h"
#include "includes/Song.h"
#include "includes/Playlist.h"
#include "includes/Artist.h"
#include "includes/Podcast.h"
#include "includes/Utility.h"
#include "includes/EnvironmentSetup.h"
#include "includes/SongCollection.h"
#include "includes/ArtistCollection.h"

#include <SFML/Graphics.hpp>

int main() {
    const EnvironmentSetup envSetup;

    constexpr SongCollection song_collection;

    std::string input;
    Playlist playlist("User");
    while(true) {
        std::cout << "Enter the name of the song you want to play, type 'playlist' to add songs to the playlist, "
                  << "'play playlist', 'info song' for info about a song or type 'exit' to quit: " << std::endl;
        std::getline(std::cin, input);

        if(input == "exit") {
            break;
        }

        if(input == "playlist") {
            while(true) {
                std::cout << "Type the name of a song that you want to add or type 'exit': " << std::endl;
                std::getline(std::cin, input);

                if(input == "exit") {
                    break;
                }

                std::shared_ptr<Song> song = API::searchSpotifySong(envSetup.getAccessToken(), input);
                playlist.addSong(song);
            }
            playlist.calculateLength();
            std::cout << "Playlist modified! The length is: " << playlist.getLength()
                      << ". If you want to shuffle it type 'Y' or if not 'N': " << std::endl;
            std::getline(std::cin, input);
            if(input == "Y") { playlist.shuffle(); }
            continue;
        }

        if (input == "play playlist") { playlist.play(envSetup.getYoutubeAPI()); continue; }

        if (input.substr(0,4) == "info") {
            std::string song_name = input.substr(5);

            std::shared_ptr<Song> song = song_collection.searchSongByName(song_name);
            if (song == nullptr) {
                song = API::searchSpotifySong(envSetup.getAccessToken(), song_name);
                std::cout << *song << std::endl;
                continue;
            }
            std::cout << *song << std::endl;
            continue;
        }

        const std::shared_ptr<Song> song = API::searchSpotifySong(envSetup.getAccessToken(), input);
        song->play(envSetup.getYoutubeAPI());
    }

    std::cout << "App closed!" << std::endl;

    /*sf::RenderWindow window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    if (!font.loadFromFile("fonts/Franie-Regular.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    sf::Text text("Hello World", font, 50);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);

    text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(text);
        window.display();
    }*/

    return 0;
}

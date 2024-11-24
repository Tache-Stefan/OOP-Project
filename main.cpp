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

#include <SFML/Window.hpp>

///verificat .. / in downloadAudio

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

    /*sf::Window window(sf::VideoMode(800, 600), "Music Manager");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }*/

    return 0;
}

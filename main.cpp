#include <iostream>
#include <fstream>
#include <string>
#include <atomic>
#include <filesystem>

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

#include "includes/PlaylistDisplay.h"
#include "includes/TextBoxTab.h"
#include "includes/TextBoxWrite.h"

//clasa TextBox devine doar un rectangle cu text
//fac derivata TextBoxWrite care e un fel de search music
//fac derivata TextBoxTab care e ca un tab
//cum fac currenttab?

int main() {
    const EnvironmentSetup envSetup;

    /*constexpr SongCollection song_collection;

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

    std::cout << "App closed!" << std::endl;*/

    sf::RenderWindow window(sf::VideoMode(1200, 700), "Music Manager", sf::Style::Default);
    window.setFramerateLimit(30);

    int currentTab = 1;

    sf::Font font;
    if (!font.loadFromFile("fonts/Franie-Regular.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    TextBoxWrite inputMusic(sf::RectangleShape(sf::Vector2f(400, 50)), sf::Color::White, font,
        sf::Text("", font, 24), sf::Color::Black);

    sf::RectangleShape searchBox(sf::Vector2f(200, 50));
    searchBox.setPosition(0, 0);
    sf::Text searchText("Search music", font, 20);
    searchText.setPosition(20, 12);

    TextBoxTab searchTab(searchBox, sf::Color::Green, font, searchText, sf::Color::Black);

    searchTab.setOnClickCallback([&currentTab] {
        currentTab = 1;
    });

    sf::RectangleShape playlistsBox(sf::Vector2f(200, 50));
    playlistsBox.setPosition(200, 0);
    sf::Text playlistsText("Playlists", font, 20);
    playlistsText.setPosition(250, 12);

    TextBoxTab playlistsTab(playlistsBox, sf::Color::Green, font, playlistsText, sf::Color::Black);

    playlistsTab.setOnClickCallback([&currentTab] {
        currentTab = 2;
    });

    PlaylistDisplay playlistDisplay(font);
    std::string userInput;
    std::atomic<bool> stopPlayback(false);
    std::atomic<bool> isMusicPlaying(false);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stopPlayback = true;
                window.close();
            }

            if (!inputMusic.getActive() && isMusicPlaying && event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::S) {
                stopPlayback = true;
                std::cout << "Playback stopped!" << std::endl;
            }

            if (currentTab == 1) {
                inputMusic.handleEvents(window, event, stopPlayback, isMusicPlaying, userInput);
            }
            if (currentTab == 2) {
                playlistDisplay.handleEvents(window, event);
            }
            searchTab.handleEvents(window, event);
            playlistsTab.handleEvents(window, event);
        }

        switch (currentTab) {
            case 1:
                window.clear();
                inputMusic.centerShape(window);
                inputMusic.draw(window);
                searchTab.draw(window);
                playlistsTab.draw(window);
                window.display();
            break;
            case 2:
                window.clear();
                playlistDisplay.draw(window);
                searchTab.draw(window);
                playlistsTab.draw(window);
                window.display();
            break;
            default:
                window.clear();
                searchTab.draw(window);
                playlistsTab.draw(window);
                window.display();
            break;
        }
    }

    return 0;
}

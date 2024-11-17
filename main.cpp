#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>
#include <atomic>
#include <thread>

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "includes/API.h"
#include "includes/Song.h"
#include "includes/Playlist.h"
#include "includes/Artist.h"
#include "includes/Podcast.h"

bool downloadAudio(const std::string &youtubeUrl, const std::string &outputFile) {
    const std::string command = "yt-dlp -f bestaudio --extract-audio --audio-format mp3 -o " + outputFile + " " + youtubeUrl;

    std::cout << "Downloading audio from YouTube..." << std::endl;
    const int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Error: Failed to download audio!" << std::endl;
        return false;
    }

    std::cout << "Audio downloaded to: " << outputFile << std::endl;
    return true;
}

void playAudio(const std::string &filePath, std::atomic<bool> &stopPlayback) {
    {
        sf::Music music;
        if (!music.openFromFile(filePath)) {
            std::cerr << "Error: Failed to open audio file!" << std::endl;
            stopPlayback = true;
            return;
        }

        std::cout << "Playing audio... Type 'stop' to stop playback." << std::endl;
        music.play();

        while (music.getStatus() == sf::SoundSource::Playing) {
            if(stopPlayback.load()) {
                std::cout << "Stopping playback..." << std::endl;
                music.stop();
                break;
            }
            sf::sleep(sf::milliseconds(100));
        }

        stopPlayback.store(true);
        std::cout << "Audio finished!" << std::endl;
    }

    if (std::filesystem::exists(filePath)) {
        try {
            std::filesystem::remove(filePath);
            std::cout << "File removed: " << filePath << std::endl;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    } else {
        std::cerr << "Error: File does not exist: " << filePath << std::endl;
    }
}

void monitorInput(std::atomic<bool> &stopPlayback) {
    std::string input;
    while(!stopPlayback.load()) {
        std::getline(std::cin, input);
        if(input == "stop") {
            stopPlayback.store(true);
            break;
        }
    }
    std::cin.clear();
}

int main() {
    const char* client_id_env = getenv("SPOTIFY_CLIENT_ID");
    const char* client_secret_env = getenv("SPOTIFY_CLIENT_SECRET");
    const char* youtube_api_env = getenv("YOUTUBE_DATA_API");
    std::string client_id;
    std::string client_secret;
    std::string youtube_api;
    bool envSet = false;

    if(!client_id_env || !client_secret_env || !youtube_api_env) {
        std::cerr << "Error: Environment variables not set!" << std::endl;
        client_id = "";
        client_secret = "";
        youtube_api_env = "";
    }
    else {
        client_id = client_id_env;
        client_secret = client_secret_env;
        youtube_api = youtube_api_env;
        envSet = true;
    }

    const std::shared_ptr<Song> TalkingToTheMoon = std::make_shared<Song>("Talking to the moon", "00:3:35");
    const std::shared_ptr<Song> DieWithASmile = std::make_shared<Song>("Die with a smile", "00:04:13");
    const std::shared_ptr<Song> ThatWhatILike = std::make_shared<Song>("That's What I Like", "00:03:30");
    const std::shared_ptr<Artist> BrunoMars = std::make_shared<Artist>("Bruno Mars");
    const std::shared_ptr<Artist> LadyGaga = std::make_shared<Artist>("Lady Gaga");

    BrunoMars->addSong(TalkingToTheMoon);
    BrunoMars->addSong(DieWithASmile);
    BrunoMars->addSong(ThatWhatILike);
    LadyGaga->addSong(DieWithASmile);
    TalkingToTheMoon->addArtist(BrunoMars);
    DieWithASmile->addArtist(BrunoMars);
    DieWithASmile->addArtist(LadyGaga);
    ThatWhatILike->addArtist(BrunoMars);

    std::vector<std::shared_ptr<Song>> sharedSongs;
    sharedSongs.push_back(TalkingToTheMoon);
    sharedSongs.push_back(DieWithASmile);
    sharedSongs.push_back(ThatWhatILike);

    Playlist Favorites{"Favorites", sharedSongs};
    Favorites.calculateLength();
    std::cout << Favorites.getLength() << std::endl;

    std::cout << TalkingToTheMoon->getLength() << std::endl;

    TalkingToTheMoon->play();

    Favorites.shuffle();
    std::cout << Favorites;

    const Podcast TheJoeRoganExperience{"The Joe Rogan Experience", "3:37:59", 2000};
    std::cout << TheJoeRoganExperience;
    TheJoeRoganExperience.play();

    if(envSet) {
        std::string access_token = API::getSpotifyAccessToken(client_id, client_secret);
        if (!access_token.empty()) {
            std::cout << "Access token retrieved successfully." << std::endl;
        } else {
            std::cerr << "Error: Failed to retrieve access token." << std::endl;
        }

        API::searchSpotify(access_token, "Talking to the moon", "track");
    }

    const std::string youtubeUrl = "https://www.youtube.com/watch?v=qrO4YZeyl0I&";
    const std::string outputFile = "audio.mp3";
    if (!downloadAudio(youtubeUrl, outputFile)) {
        return 1;
    }

    std::atomic<bool> stopPlayback(false);
    std::thread inputThread(monitorInput, std::ref(stopPlayback));
    playAudio(outputFile, stopPlayback);

    inputThread.join();

    return 0;
}

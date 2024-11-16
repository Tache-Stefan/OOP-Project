#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <libenvpp/env.hpp>

#include <SFML/Audio.hpp>

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

void playAudio(const std::string &filePath) {
    sf::Music music;
    if (!music.openFromFile(filePath)) {
        std::cerr << "Error: Failed to open audio file!" << std::endl;
        return;
    }

    std::cout << "Playing audio..." << std::endl;
    music.play();

    while (music.getStatus() == sf::SoundSource::Playing) {
        sf::sleep(sf::milliseconds(100));
    }

    std::cout << "Audio finished!" << std::endl;
}

int main() {
    /*auto pre = env::prefix("SPOTIFY");

    const auto client_id_pre = pre.register_variable<std::string>("CLIENT_ID");
    const auto client_secret_pre = pre.register_variable<std::string>("CLIENT_SECRET");
    const auto parsed_and_validated_pre = pre.parse_and_validate();

    std::string client_id = "";
    std::string client_secret = "";

    if (parsed_and_validated_pre.ok()) {
        client_id = parsed_and_validated_pre.get_or(client_id_pre, "default_client_id");
        client_secret = parsed_and_validated_pre.get_or(client_secret_pre, "default_client_secret");
    } else {
        std::cout << "Warnings: " << parsed_and_validated_pre.warning_message() << std::endl;
        std::cout << "Errors: " << parsed_and_validated_pre.error_message() << std::endl;
        return 1;
    }*/

    std::string client_id = getenv("SPOTIFY_CLIENT_ID");
    std::string client_secret = getenv("SPOTIFY_CLIENT_SECRET");

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

    if (client_id == "" || client_secret == "") {
        std::cerr << "Error: Environment variables for Spotify credentials are not set." << std::endl;
        return 1;
    }

    std::string access_token = API::getSpotifyAccessToken(client_id, client_secret);
    if (!access_token.empty()) {
        std::cout << "Access token retrieved successfully." << std::endl;
    } else {
        std::cerr << "Error: Failed to retrieve access token." << std::endl;
    }

    std::string song_url = API::searchSpotify(access_token, "Talking to the moon", "track");

    if(!song_url.empty()) {
        std::cout << song_url;
    }

    const std::string youtubeUrl = "https://www.youtube.com/watch?v=qrO4YZeyl0I&";
    const std::string outputFile = "downloaded_audio.mp3";
    if (!downloadAudio(youtubeUrl, outputFile)) {
        return 1;
    }

    playAudio(outputFile);

    return 0;
}

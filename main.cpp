#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <atomic>
#include <thread>

#include "includes/API.h"
#include "includes/Song.h"
#include "includes/Playlist.h"
#include "includes/Artist.h"
#include "includes/Podcast.h"
#include "includes/Utility.h"

int main() {
    Utils::loadEnvFile();

    const char* client_id_env = getenv("SPOTIFY_CLIENT_ID");
    const char* client_secret_env = getenv("SPOTIFY_CLIENT_SECRET");
    const char* youtube_api_env = getenv("YOUTUBE_DATA_API");
    std::string client_id;
    std::string client_secret;
    std::string youtube_api;
    bool envSet = false;

    if(!client_id_env || !client_secret_env || !youtube_api_env) {
        std::cerr << "Error: Spotify or Youtube API keys missing!" << std::endl;
        client_id = "";
        client_secret = "";
        youtube_api = "";
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

    const std::string youtubeURL = API::searchYouTube(youtube_api, "Talking To The Moon");
    const std::string outputFile = "audio.mp3";
    if (!Utils::downloadAudio(youtubeURL, outputFile)) {
        return 1;
    }

    std::atomic<bool> stopPlayback(false);
    std::thread inputThread(Utils::monitorInput, std::ref(stopPlayback));
    Utils::playAudio(outputFile, stopPlayback);

    inputThread.join();

    return 0;
}

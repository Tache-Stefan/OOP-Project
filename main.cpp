#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "includes/Song.h"
#include "includes/Playlist.h"
#include "includes/Artist.h"
#include "includes/Utility.h"

int main() {
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

    const char* client_id = std::getenv("SPOTIFY_CLIENT_ID");
    const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

    if (!client_id || !client_secret) {
        std::cerr << "Error: Environment variables for Spotify credentials are not set." << std::endl;
        return 1;
    }

    std::string access_token = Utils::getSpotifyAccessToken(client_id, client_secret);
    if (!access_token.empty()) {
        std::cout << "Access token retrieved successfully." << std::endl;
    } else {
        std::cerr << "Error: Failed to retrieve access token." << std::endl;
    }

    return 0;
}

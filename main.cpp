#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>

#include "includes/API.h"
#include "includes/Song.h"
#include "includes/Playlist.h"
#include "includes/Artist.h"
#include "includes/Podcast.h"
#include "includes/Utility.h"
#include "includes/EnvironmentSetup.h"

//verificat .. / in downloadAudio
//folosit playlist si tot ce am etc.

int main() {
    const EnvironmentSetup envSetup;
    std::string access_token = "";

    if(envSetup.isEnvSet()) {
        access_token = envSetup.retrieveSpotifyAccessToken();
        if(!access_token.empty()) {
            std::cout << "Access token retrieved successfully." << std::endl;
        }
        else {
            std::cerr << "Error: Failed to retrieve access token." << std::endl;
        }
    }

    const std::shared_ptr<Song> TalkingToTheMoon = std::make_shared<Song>("when i was older", "00:03:35");
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
    //std::cout << Favorites.getLength() << std::endl;

    //std::cout << TalkingToTheMoon->getLength() << std::endl;

    //Favorites.shuffle();
    //std::cout << Favorites;

    //const Podcast TheJoeRoganExperience{"The Joe Rogan Experience", "3:37:59", 2000};
    //std::cout << TheJoeRoganExperience;

    std::cout << "Choose a song to play (Talking To The Moon - 1, Die with a smile - 2, That's What I Like - 3) or 0 for exit: " << std::endl;
    int userInput = 0;
    while(true) {
        std::cin >> userInput;
        if(userInput == 0)
            break;
        if(userInput == 1)
            TalkingToTheMoon->play(envSetup.getYoutubeAPI());
        if(userInput == 2)
            DieWithASmile->play(envSetup.getYoutubeAPI());
        if(userInput == 3)
            ThatWhatILike->play(envSetup.getYoutubeAPI());
    }

    std::cout << "App closed!" << std::endl;
    return 0;
}

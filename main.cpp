#include <iostream>
#include <string>
#include <vector>

#include "includes/Song.h"
#include "includes/Playlist.h"
#include "includes/Artist.h"

int main() {
    const std::shared_ptr<Song> TalkingToTheMoon = std::make_shared<Song>("Talking to the moon", "00:3:35");
    const std::shared_ptr<Song> DieWithASmile = std::make_shared<Song>("Die with a smile", "00:04:13");
    const std::shared_ptr<Artist> BrunoMars = std::make_shared<Artist>("Bruno Mars");
    const std::shared_ptr<Artist> LadyGaga = std::make_shared<Artist>("Lady Gaga");

    BrunoMars->addSong(TalkingToTheMoon);
    BrunoMars->addSong(DieWithASmile);
    LadyGaga->addSong(DieWithASmile);
    TalkingToTheMoon->addArtist(BrunoMars);
    DieWithASmile->addArtist(BrunoMars);
    DieWithASmile->addArtist(LadyGaga);

    std::vector<std::shared_ptr<Song>> sharedSongs;
    sharedSongs.push_back(TalkingToTheMoon);
    sharedSongs.push_back(DieWithASmile);

    Playlist Favorites{"Favorites", sharedSongs};
    Favorites.calculateLength();
    std::cout << Favorites.getLength() << std::endl;

    std::cout << TalkingToTheMoon->getLength() << std::endl;

    TalkingToTheMoon->play();

    return 0;
}

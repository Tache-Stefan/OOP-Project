#include <iostream>
#include <string>
#include <vector>

#include "includes/Song.h"
#include "includes/Playlist.h"
#include "includes/Artist.h"

int main() {
    Song TalkingToTheMoon{"Talking to the moon", "00:3:35"};
    Song DieWithASmile{"Die with a smile", "00:04:13"};
    Artist BrunoMars{"Bruno Mars"};
    Artist LadyGaga{"Lady Gaga"};

    BrunoMars.addSong(TalkingToTheMoon);
    BrunoMars.addSong(DieWithASmile);
    LadyGaga.addSong(DieWithASmile);
    TalkingToTheMoon.addArtist(BrunoMars);
    DieWithASmile.addArtist(BrunoMars);
    DieWithASmile.addArtist(LadyGaga);

    std::vector<Song> songs;
    songs.push_back(TalkingToTheMoon);
    songs.push_back(DieWithASmile);

    Playlist Favorites{"Favorites", songs};
    Favorites.calculateLength();
    std::cout << Favorites.getLength() << std::endl;

    std::cout << TalkingToTheMoon.getLength() << std::endl;

    TalkingToTheMoon.play();

    return 0;
}
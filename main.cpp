#include <iostream>
#include <string>
#include <vector>

#include "includes/Song.h"
#include "includes/Playlist.h"
#include "includes/Artist.h"

/*struct time {
    int hours;
    int minutes;
    int seconds;
};*/
//TODO: implementare length cu struct asta

int main() {
    Song TalkingToTheMoon{"Talking to the moon", 3.35f};
    Song DieWithASmile{"Die with a smile", 4.13f};
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
    return 0;
}
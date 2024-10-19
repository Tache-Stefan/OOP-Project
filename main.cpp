#include <iostream>
#include <string>
#include <vector>

class Song;
class Playlist;
class Artist;

/*struct time {
    int hours;
    int minutes;
    int seconds;
};*/
//TODO: implementare length cu struct asta

class Song {
private:
    std::string title;
    float length;
    std::vector<Artist> artists;
public:
    Song(const std::string& title_, const float length_, const std::vector<Artist> &artists_) : title(title_), length(length_), artists(artists_) {
        std::cout << "Song(+artist): " << title << std::endl;
    }
    Song(const std::string& title_, const float length_) : title(title_), length(length_) {
        std::cout << "Song: " << title << std::endl;
    }
    Song(const Song& other) : title(other.title), length(other.length), artists(other.artists) {
        std::cout << "Song(copiere)" << std::endl;
    }
    Song& operator=(const Song& other) {
        title = other.title;
        length = other.length;
        artists = other.artists;
        std::cout << "Song(operator=)" << std::endl;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Song& song) {
        os << "Song: " << song.title << ", " << song.length << "\n";
        return os;
    }
    ~Song() {std::cout << "Song(destr)" << std::endl; }
    float getLength() const {return length;}
    void addArtist(const Artist& artist) {
        artists.push_back(artist);
    }
};

class Playlist {
private:
    std::string title;
    std::vector<Song> songs;
    float length;
public:
    Playlist(const std::string& title_, const std::vector<Song> &songs_, const float length_ = 0) : title(title_), songs(songs_), length(length_) {
        std::cout << "Playlist: " << title << "\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
        os << "Playlist: " << playlist.title << "\n";
        return os;
    }
    float getLength() const {return length;}
    void calculateLength() {
        float aux = 0;
        for(const auto& song : songs)
            aux += song.getLength();
        length = aux;
    }
};

class Artist {
private:
    std::string name;
    std::vector<Song> songs;
public:
    Artist(const std::string& name_, const std::vector<Song> &songs_) : name(name_), songs(songs_) {
        std::cout << "Artist(+songs): " << name << std::endl;
    }
    explicit Artist(const std::string& name) {
        std::cout << "Artist: " << name << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Artist& artist) {
        os << "Artist: " << artist.name << std::endl;
        return os;
    }
    void addSong(const Song& song) {
        songs.push_back(song);
    }
};

int main() {
    Song TalkingToTheMoon{"Talking to the moon", 3.35};
    Song DieWithASmile{"Die with a smile", 4.13};
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
#pragma once
#include <atomic>
#include <memory>

#include "SFML/Audio.hpp"

class MusicPlayer {
private:
    static std::string filePath;
    static std::atomic<bool> stopPlayback;
    static std::atomic<bool> isMusicPlaying;
    static std::atomic<bool> loadingMusic;
    static std::atomic<int> volume;
    static std::atomic<bool> seekToStart;
    static std::atomic<bool> seekToEnd;
    static std::atomic<bool> skipBack;
    static std::atomic<bool> skipForward;
    static std::atomic<bool> playlistPlaying;
    static std::atomic<std::shared_ptr<std::string>> currentSong;
public:
    static void playMusic();
    static void increaseVolume();
    static void decreaseVolume();
    static void setStopPlayback(bool stopPlayback_);
    static void setIsMusicPlaying(bool isMusicPlaying_);
    static void setLoadingMusic(bool loadingMusic_);
    static void setSeekToStart(bool seekToStart_);
    static void setSeekToEnd(bool seekToEnd_);
    static void setSkipBack(bool skipBack_);
    static void setSkipForward(bool skipForward_);
    static void setPlaylistPlaying(bool playlistPlaying_);
    static void setCurrentSong(const std::string &currentSong_);
    static bool getStopPlayback();
    static bool getIsMusicPlaying();
    static bool getLoadingMusic();
    static bool getPlaylistPlaying();
    static std::shared_ptr<std::string> getCurrentSong();
};

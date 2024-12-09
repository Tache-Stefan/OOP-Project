#pragma once
#include <atomic>

#include "SFML/Audio.hpp"

class MusicPlayer {
private:
    static std::string filePath;
    static std::atomic<bool> stopPlayback;
    static std::atomic<bool> isMusicPlaying;
    static std::atomic<bool> loadingMusic;
public:
    static void playMusic();
    static void setStopPlayback(bool stopPlayback_);
    static void setIsMusicPlaying(bool isMusicPlaying_);
    static void setLoadingMusic(bool loadingMusic_);
    static bool getStopPlayback();
    static bool getIsMusicPlaying();
    static bool getLoadingMusic();
};

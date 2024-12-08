#pragma once
#include <atomic>

#include "SFML/Audio.hpp"

class MusicPlayer {
private:
    static std::string filePath;
    static std::atomic<bool> stopPlayback;
    static std::atomic<bool> isMusicPlaying;
public:
    static void playMusic();
    static void setStopPlayback(bool stopPlayback_);
    static void setIsMusicPlaying(bool isMusicPlaying_);
    static bool getStopPlayback();
    static bool getIsMusicPlaying();
};

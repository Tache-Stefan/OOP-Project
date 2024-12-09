#include "MusicPlayer.h"

#include <iostream>
#include <filesystem>

#include "Exceptions.h"

std::atomic<bool> MusicPlayer::stopPlayback = false;
std::atomic<bool> MusicPlayer::isMusicPlaying = false;
std::atomic<bool> MusicPlayer::loadingMusic = false;
std::string MusicPlayer::filePath = "audio.mp3";

void MusicPlayer::playMusic() {
    stopPlayback.store(false);
    isMusicPlaying.store(false);

    {
        sf::Music music;
        if (!music.openFromFile(filePath)) {
            std::cerr << "Error: Failed to open audio file!" << std::endl;
            loadingMusic.store(false);
            stopPlayback.store(true);
            return;
        }

        loadingMusic.store(false);
        isMusicPlaying.store(true);
        music.play();

        while (music.getStatus() == sf::SoundSource::Playing) {
            if(stopPlayback.load()) {
                std::cout << "Stopping playback..." << std::endl;
                music.stop();
                break;
            }
            sleep(sf::milliseconds(100));
        }

        isMusicPlaying.store(false);
        stopPlayback.store(true);
        std::cout << "Audio finished!" << std::endl;
    }

    if (std::filesystem::exists(filePath)) {
        try {
            std::filesystem::remove(filePath);
            std::cout << "File removed: " << filePath << std::endl;
        } catch (FileRemoverException& e) {
            std::cerr << e.what() << std::endl;
        }
    } else {
        std::cerr << "Error: File does not exist: " << filePath << std::endl;
    }
}

void MusicPlayer::setStopPlayback(const bool stopPlayback_) { stopPlayback.store(stopPlayback_); }

void MusicPlayer::setIsMusicPlaying(const bool isMusicPlaying_) { isMusicPlaying.store(isMusicPlaying_); }

void MusicPlayer::setLoadingMusic(const bool loadingMusic_) { loadingMusic.store(loadingMusic_); }

bool MusicPlayer::getStopPlayback() { return stopPlayback.load(); }

bool MusicPlayer::getIsMusicPlaying() { return isMusicPlaying.load(); }

bool MusicPlayer::getLoadingMusic() { return loadingMusic.load(); }

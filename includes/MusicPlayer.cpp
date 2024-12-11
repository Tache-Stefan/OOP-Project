#include "MusicPlayer.h"

#include <iostream>
#include <filesystem>

#include "Exceptions.h"

std::atomic<bool> MusicPlayer::stopPlayback = false;
std::atomic<bool> MusicPlayer::isMusicPlaying = false;
std::atomic<bool> MusicPlayer::loadingMusic = false;
std::atomic<int> MusicPlayer::volume = 100;
std::atomic<bool> MusicPlayer::seekToStart = false;
std::atomic<bool> MusicPlayer::seekToEnd = false;
std::atomic<bool> MusicPlayer::skipBack = false;
std::atomic<bool> MusicPlayer::skipForward = false;
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

        music.setVolume(volume);
        loadingMusic.store(false);
        isMusicPlaying.store(true);
        music.play();

        while (music.getStatus() == sf::SoundSource::Playing) {
            if(stopPlayback.load()) {
                std::cout << "Stopping playback..." << std::endl;
                music.stop();
                break;
            }
            music.setVolume(volume.load());
            if (seekToStart.load()) {
                music.setPlayingOffset(sf::seconds(0));
                seekToStart.store(false);
            }
            if (seekToEnd.load()) {
                music.setPlayingOffset(music.getDuration());
                seekToEnd.store(false);
            }
            if (skipBack.load()) {
                sf::Time newOffset = music.getPlayingOffset() - sf::seconds(10);
                if (newOffset < sf::seconds(0)) {
                    newOffset = sf::seconds(0);
                }
                music.setPlayingOffset(newOffset);
                skipBack.store(false);
            }
            if (skipForward.load()) {
                sf::Time newOffset = music.getPlayingOffset() + sf::seconds(10);
                if (newOffset > music.getDuration()) {
                    newOffset = music.getDuration();
                }
                music.setPlayingOffset(newOffset);
                skipForward.store(false);
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

void MusicPlayer::increaseVolume() {
    const int newVolume = std::min(volume.load() + 10, 100);
    volume.store(newVolume);
}

void MusicPlayer::decreaseVolume() {
    const int newVolume = std::max(volume.load() - 10, 0);
    volume.store(newVolume);
}

void MusicPlayer::setStopPlayback(const bool stopPlayback_) { stopPlayback.store(stopPlayback_); }

void MusicPlayer::setIsMusicPlaying(const bool isMusicPlaying_) { isMusicPlaying.store(isMusicPlaying_); }

void MusicPlayer::setLoadingMusic(const bool loadingMusic_) { loadingMusic.store(loadingMusic_); }

void MusicPlayer::setSeekToStart(const bool seekToStart_) { seekToStart.store(seekToStart_); }

void MusicPlayer::setSeekToEnd(const bool seekToEnd_) { seekToEnd.store(seekToEnd_); }

void MusicPlayer::setSkipBack(const bool skipBack_) { skipBack.store(skipBack_); }

void MusicPlayer::setSkipForward(const bool skipForward_) { skipForward.store(skipForward_); }

bool MusicPlayer::getStopPlayback() { return stopPlayback.load(); }

bool MusicPlayer::getIsMusicPlaying() { return isMusicPlaying.load(); }

bool MusicPlayer::getLoadingMusic() { return loadingMusic.load(); }

#include "../headers/MusicPlayer.h"

#include <iostream>
#include <filesystem>

#include "../headers/Exceptions.h"

std::atomic<bool> MusicPlayer::paused = false;
std::atomic<bool> MusicPlayer::stopPlayback = false;
std::atomic<bool> MusicPlayer::isMusicPlaying = false;
std::atomic<bool> MusicPlayer::loadingMusic = false;
std::atomic<int> MusicPlayer::volume = 100;
std::atomic<bool> MusicPlayer::seekToStart = false;
std::atomic<bool> MusicPlayer::seekToEnd = false;
std::atomic<bool> MusicPlayer::skipBack = false;
std::atomic<bool> MusicPlayer::skipForward = false;
std::atomic<bool> MusicPlayer::playlistPlaying = false;
std::string MusicPlayer::currentSong;
std::mutex MusicPlayer::songMutex;
sf::Time MusicPlayer::elapsedTime = sf::Time::Zero;
sf::Time MusicPlayer::totalTime = sf::Time::Zero;
std::string MusicPlayer::filePath = "audio.mp3";

[[maybe_unused]] MusicPlayer& MusicPlayer::getInstance() {
    static MusicPlayer instance;
    return instance;
}

// cppcheck-suppress unusedFunction ; false positive
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
        totalTime = music.getDuration();
        music.play();

        while (music.getStatus() == sf::SoundSource::Playing || music.getStatus() == sf::SoundSource::Paused) {
            if(stopPlayback.load()) {
                std::cout << "Stopping playback..." << std::endl;
                music.stop();
                break;
            }
            if (paused.load() && music.getStatus() == sf::SoundSource::Playing) {
                music.pause();
            } else if (!paused.load() && music.getStatus() == sf::SoundSource::Paused) {
                music.play();
            }
            elapsedTime = music.getPlayingOffset();
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

        elapsedTime = sf::Time::Zero;
        totalTime = sf::Time::Zero;
        paused.store(false);
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

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::increaseVolume() {
    const int newVolume = std::min(volume.load() + 10, 100);
    volume.store(newVolume);
}

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::decreaseVolume() {
    const int newVolume = std::max(volume.load() - 10, 0);
    volume.store(newVolume);
}

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setPaused(const bool paused_) { paused.store(paused_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setStopPlayback(const bool stopPlayback_) { stopPlayback.store(stopPlayback_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setIsMusicPlaying(const bool isMusicPlaying_) { isMusicPlaying.store(isMusicPlaying_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setLoadingMusic(const bool loadingMusic_) { loadingMusic.store(loadingMusic_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setSeekToStart(const bool seekToStart_) { seekToStart.store(seekToStart_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setSeekToEnd(const bool seekToEnd_) { seekToEnd.store(seekToEnd_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setSkipBack(const bool skipBack_) { skipBack.store(skipBack_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setSkipForward(const bool skipForward_) { skipForward.store(skipForward_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setPlaylistPlaying(const bool playlistPlaying_) { playlistPlaying.store(playlistPlaying_); }

// cppcheck-suppress unusedFunction ; false positive
void MusicPlayer::setCurrentSong(const std::string& currentSong_) {
    std::lock_guard lock(songMutex);
    currentSong = currentSong_;
}

bool MusicPlayer::getPaused() { return paused.load(); }

bool MusicPlayer::getIsMusicPlaying() { return isMusicPlaying.load(); }

// cppcheck-suppress unusedFunction ; false positive
bool MusicPlayer::getLoadingMusic() { return loadingMusic.load(); }

// cppcheck-suppress unusedFunction ; false positive
bool MusicPlayer::getPlaylistPlaying() { return playlistPlaying.load(); }

// cppcheck-suppress unusedFunction ; false positive
std::string MusicPlayer::getCurrentSong() {
    std::lock_guard lock(songMutex);
    return currentSong;
}

// cppcheck-suppress unusedFunction ; false positive
sf::Time MusicPlayer::getElapsedTime() { return elapsedTime; }

// cppcheck-suppress unusedFunction ; false positive
sf::Time MusicPlayer::getTotalTime() { return totalTime; }

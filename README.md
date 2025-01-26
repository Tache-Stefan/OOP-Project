# Music Manager

## Description
Music Manager is an app that allows you to play all of your favorite songs
while also enabling you to organize them in as many playlists as you want. 
The app comes complete with intuitive playback and volume controls. 
Internet connection is required.

## Prerequisites

Linux:
```sh
sudo apt-get update && sudo apt-get install yt-dlp
sudo apt-get update && sudo apt-get install ffmpeg
```

macOS:
```sh
brew install yt-dlp
brew install ffmpeg
```

Windows:
```sh
winget install --id=yt-dlp.yt-dlp  -e
winget install --id=Gyan.FFmpeg  -e
```

## API keys

The API keys need to be placed in **envconfig.txt**. <br>
- Spotify API keys are obtainable [here](https://developer.spotify.com/). <br>
- Youtube Data API keys are obtainable [here](https://console.cloud.google.com/).

## Compilation instructions

The project is configured using CMake.

0. Required libraries for Linux:
```sh
sudo apt-get update && \
  sudo apt-get install libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    libfreetype6-dev
```

1. Configuration step:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

or Windows:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
```

2. Compilation step:
```sh
cmake --build build --config Debug --parallel 6
```

3. Installation step (optional):
```sh
cmake --install build --config Debug --prefix install_dir
```

Also see [`scripts/cmake.sh`](scripts/cmake.sh).

## Resources

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL)
- [CPR](https://github.com/libcpr/cpr)
- [nlohmann/json](https://github.com/nlohmann/json)
- [Spotify API](https://developer.spotify.com/)
- [yt-dlp](https://github.com/yt-dlp/yt-dlp)
- [ffmpeg](https://www.ffmpeg.org/)
- [Youtube Data API](https://developers.google.com/youtube/v3)
- [FranieFont](https://www.dafontfree.io/franie-font/)
- [CoolveticaFont](https://www.dafont.com/coolvetica.font)

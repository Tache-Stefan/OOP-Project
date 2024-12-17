cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)

###############################################################################

# external dependencies with FetchContent

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# din cauza SFML
set(WARNINGS_AS_ERRORS OFF)

# NOTE: Also update SFML_VERSION env var in .github/workflows/cmake.yml:84
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
    # GIT_TAG        69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
    # GIT_TAG        origin/master
    GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
)

FetchContent_MakeAvailable(SFML)

if(GITHUB_ACTIONS)
    set(CPR_VERSION "1.10.5")
else()
    set(CPR_VERSION "1.11.0")
endif()

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG ${CPR_VERSION}
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

execute_process(
        COMMAND ${Python3_EXECUTABLE} -m pip show yt-dlp
        RESULT_VARIABLE YT_DLP_NOT_FOUND
        OUTPUT_QUIET
        ERROR_QUIET
)

if(YT_DLP_NOT_FOUND)
    message(STATUS "yt-dlp not found, installing with pip.")
    execute_process(
            COMMAND ${Python3_EXECUTABLE} -m pip install yt-dlp
    )
else()
    message(STATUS "yt-dlp is already installed.")
endif()

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME}
    main.cpp
    generated/src/Helper.cpp
    env_fixes.h
        main.cpp
        src/Song.cpp
        headers/Song.h
        src/Playlist.cpp
        headers/Playlist.h
        src/Artist.cpp
        headers/Artist.h
        headers/Utility.h
        src/Utility.cpp
        src/MediaItem.cpp
        headers/MediaItem.h
        src/API.cpp
        headers/API.h
        src/EnvironmentSetup.cpp
        headers/EnvironmentSetup.h
        src/SongCollection.cpp
        headers/SongCollection.h
        src/ArtistCollection.cpp
        headers/ArtistCollection.h
        src/TextBoxWrite.cpp
        headers/TextBoxWrite.h
        src/TextBox.cpp
        headers/TextBox.h
        src/TextBoxTab.cpp
        headers/TextBoxTab.h
        src/PlaylistDisplay.cpp
        headers/PlaylistDisplay.h
        src/TextBoxPlaylist.cpp
        headers/TextBoxPlaylist.h
        src/SongDisplay.cpp
        headers/SongDisplay.h
        src/TextBoxDelete.cpp
        headers/TextBoxDelete.h
        headers/Exceptions.h
        src/Exceptions.cpp
        src/MusicPlayer.cpp
        headers/MusicPlayer.h
        src/TextBoxButton.cpp
        headers/TextBoxButton.h
        src/Display.cpp
        headers/Display.h
        src/Application.cpp
        headers/Application.h
)

include(cmake/CompilerFlags.cmake)

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE generated/include)
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
        ${SFML_SOURCE_DIR}/include
        ${cpr_SOURCE_DIR}/include
)

target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr sfml-graphics sfml-window sfml-system sfml-audio Threads::Threads
        nlohmann_json::nlohmann_json
)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# copy dependent DLLs to build dir
# see https://en.sfml-dev.org/forums/index.php?topic=28580.0
# remove this if not using audio or if using SFML 3
if (WIN32 AND SFML_BUILD_AUDIO)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
         ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
         $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()


include(cmake/CopyHelper.cmake)
copy_files(FILES tastatura.txt envconfig.txt playlists.json DIRECTORY fonts)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)

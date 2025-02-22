#include <iostream>
#include "../headers/API.h"
#include "../headers/Utility.h"
#include "../headers/Collection.h"

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "../headers/EnvironmentSetup.h"
#include "../headers/Exceptions.h"

namespace API {
    std::string getSpotifyAccessToken(const std::string& client_id, const std::string& client_secret) {
        const std::string auth = client_id + ":" + client_secret;
        const std::string auth_encoded = Utils::base64_encode(auth);

        cpr::Header headers = {
            {"Authorization", "Basic " + auth_encoded},
            {"Content-Type", "application/x-www-form-urlencoded"}
        };
        cpr::Payload payload = {
            {"grant_type", "client_credentials"}
        };

        cpr::Response r = cpr::Post(cpr::Url{"https://accounts.spotify.com/api/token"},
                                     headers, payload);

        if (r.status_code == 200) {
            try {
                nlohmann::json jsonData = nlohmann::json::parse(r.text);

                return jsonData["access_token"].get<std::string>();
            } catch (const JsonException& e) {
                std::cerr << e.what() << std::endl;
                return "";
            }
        }

        std::cerr << "Error: " << r.status_code << " " << r.text << std::endl;
        return "";
    }

    std::shared_ptr<Song> searchSpotifySong(const std::string& query) {
        const std::string access_token = EnvironmentSetup::getAccessToken();

        cpr::Header headers = {
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        };

        const std::string url = "https://api.spotify.com/v1/search?q=" + cpr::util::urlEncode(query) + "&type=track";

        cpr::Response r = cpr::Get(cpr::Url{url}, headers);

        if (r.status_code == 200) {
            try {
                nlohmann::json jsonData = nlohmann::json::parse(r.text);

                if (!jsonData["tracks"]["items"].empty()) {
                    auto first_result = jsonData["tracks"]["items"][0];
                    const std::string song_id = first_result["id"];
                    std::shared_ptr<Song> song = Collection<Song>::getItem(song_id);

                    if (song != nullptr) {
                        return song;
                    }

                    const std::string artist_id = first_result["artists"][0]["id"];
                    const std::shared_ptr<Artist> artist = Collection<Artist>::getItem(artist_id);
                    if (artist == nullptr) {
                        const std::string artist_name = first_result["artists"][0]["name"];
                        const std::shared_ptr<Artist> artist_api = searchSpotifyArtist(artist_name);
                        Collection<Artist>::addItem(artist_api);
                        const std::string track_name = first_result["name"];
                        const struct tm length = Utils::durationToTm(first_result["duration_ms"]);
                        song = std::make_shared<Song>(track_name, artist_api, length, song_id);
                        Collection<Song>::addItem(song);
                        return song;
                    }

                    const std::string track_name = first_result["name"];
                    const struct tm length = Utils::durationToTm(first_result["duration_ms"]);
                    song = std::make_shared<Song>(track_name, artist, length, song_id);
                    Collection<Song>::addItem(song);
                    return song;
                }
                std::cerr << "No results found for query: " << query << std::endl;
                return nullptr;

            } catch (const JsonException& e) {
                std::cerr << e.what() << std::endl;
                return nullptr;
            }
        }

        std::cerr << "Error: " << r.status_code << " " << r.text << std::endl;
        return nullptr;
    }

    std::shared_ptr<Artist> searchSpotifyArtist(const std::string &query) {
        const std::string access_token = EnvironmentSetup::getAccessToken();

        cpr::Header headers = {
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        };

        const std::string url = "https://api.spotify.com/v1/search?q=" + cpr::util::urlEncode(query) + "&type=artist";

        cpr::Response r = cpr::Get(cpr::Url{url}, headers);

        if (r.status_code == 200) {
            try {
                nlohmann::json jsonData = nlohmann::json::parse(r.text);

                if (!jsonData["artists"]["items"].empty()) {
                    auto first_artist = jsonData["artists"]["items"][0];
                    const std::string artist_name = first_artist["name"];
                    const std::string id = first_artist["id"];

                    return std::make_shared<Artist>(artist_name, id);
                }
                std::cerr << "No results found for query: " << query << std::endl;
                return nullptr;

            } catch (const JsonException& e) {
                std::cerr << e.what() << std::endl;
                return nullptr;
            }
        }

        std::cerr << "Error: " << r.status_code << " " << r.text << std::endl;
        return nullptr;
    }

    std::string searchYouTube(const std::string& query) {
        const std::string youtube_api = EnvironmentSetup::getYoutubeAPI();

        const std::string url = "https://www.googleapis.com/youtube/v3/search?part=snippet&q=" +
            cpr::util:: urlEncode(query) + "&type=video&maxResults=1&key=" + youtube_api;

        cpr::Response r = cpr::Get(cpr::Url{url});

        if(r.status_code == 200) {
            try {
                nlohmann::json jsonData = nlohmann::json::parse(r.text);

                if (jsonData.contains("items") && !jsonData["items"].empty()) {
                    const std::string videoId = jsonData["items"][0]["id"]["videoId"];
                    return "https://www.youtube.com/watch?v=" + videoId;
                }
                std::cerr << "No videos found for query: " << query << std::endl;
                return "";

            } catch (const JsonException& e) {
                std::cerr << e.what() << std::endl;
                return "";
            }
        }

        std::cerr << "Error: " << r.status_code << " " << r.error.message << std::endl;
        return "";
    }
}

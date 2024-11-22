#include <iostream>
#include "Utility.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "API.h"

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
            } catch (const std::exception& e) {
                std::cerr << "Error parsing JSON response: " << e.what() << std::endl;
                return "";
            }
        } else {
            std::cerr << "Error: " << r.status_code << " " << r.text << std::endl;
            return "";
        }
    }
    Song searchSpotify(const std::string& access_token, const std::string& query, const std::string& type) {
        if(type != "album" && type != "artist" && type != "playlist" && type != "track" && type != "show" && type != "episode" && type != "audiobook") {
            std::cerr << "Invalid type specified.";
            return Song();
        }

        cpr::Header headers = {
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        };

        const std::string url = "https://api.spotify.com/v1/search?q=" + cpr::util::urlEncode(query) + "&type=" + type;

        cpr::Response r = cpr::Get(cpr::Url{url}, headers);

        if (r.status_code == 200) {
            try {
                nlohmann::json jsonData = nlohmann::json::parse(r.text);

                if (!jsonData["tracks"]["items"].empty()) {
                    auto first_result = jsonData["tracks"]["items"][0];
                    const std::string track_name = first_result["name"];
                    const std::string id = first_result["id"];
                    const struct tm length = Utils::durationToTm(first_result["duration_ms"]);
                    const std::string artist_name = first_result["artists"][0]["name"];

                    std::cout << "Track: " << track_name << "\n"
                              << "id: " << id << "\n"
                              << "length: " << length.tm_hour << ":" << length.tm_min << ":" << length.tm_sec << "\n";

                    return Song();
                }
                std::cerr << "No results found for query: " << query << std::endl;
                return Song();

            } catch (const std::exception& e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
                return Song();
            }
        }

        std::cerr << "Error: " << r.status_code << " " << r.text << std::endl;
        return Song();
    }
    std::string searchYouTube(const std::string& youtube_api, const std::string& query) {
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

            } catch (const std::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
                return "";
            }
        }

        std::cerr << "Error: " << r.status_code << " " << r.error.message << std::endl;
        return "";
    }
}

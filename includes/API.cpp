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
}
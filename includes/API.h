#pragma once

#include <iostream>
#include <string>
#include "Utility.h"
#include "cpr/cpr.h"
#include <nlohmann/json.hpp>

namespace API {
    std::string getSpotifyAccessToken(const std::string& client_id, const std::string& client_secret);
}

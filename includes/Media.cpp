#include "Media.h"
#include "Artist.h"
#include "Utility.h"

Media::Media(const std::string& title_, const std::vector<std::shared_ptr<Artist>>& artists_, const std::string& length_) : title(title_),
             artists(artists_), length(Utils::stringToTime(length_)) {}

Media::Media(const std::string& title_, const std::string& length_) : title(title_), length(Utils::stringToTime(length_)) {}

Media::Media(const Media& other) : title(other.title), artists(other.artists), length(other.length) {}

const std::string& Media::getTitle() const {return title;}
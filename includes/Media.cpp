#include "Media.h"
#include "Artist.h"

Media::Media() {};

Media::Media(const std::string& title_, const std::shared_ptr<Artist>& artist_, const struct tm& length_) : title(title_),
             artist(artist_), length(length_) {}

Media::Media(const std::string& title_, const struct tm& length_) : title(title_), length(length_) {}

Media::Media(const Media& other) : title(other.title), artist(other.artist), length(other.length) {}

const std::string& Media::getTitle() const {return title;}
#include "Media.h"
#include "Artist.h"

Media::Media() = default;

Media::Media(const std::string& title_, const std::shared_ptr<Artist>& artist_, const struct tm& length_) : title(title_),
             artist(artist_), length(length_) {}

Media::Media(const std::string& title_, const struct tm& length_) : title(title_), length(length_) {}

Media::Media(const Media& other) = default;

const std::string& Media::getTitle() const {return title;}
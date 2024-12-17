#include "../headers/MediaItem.h"
#include "../headers/Artist.h"

MediaItem::MediaItem() = default;

MediaItem::MediaItem(std::string title_, const struct tm& length_) : title(std::move(title_)), length(length_) {}

MediaItem::MediaItem(std::string title_) : title(std::move(title_)) {}

MediaItem::MediaItem(const MediaItem& other) = default;

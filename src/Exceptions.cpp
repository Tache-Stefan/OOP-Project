#include "../headers/Exceptions.h"

SearchException::SearchException(const std::string& msg) : BasicException(std::string("Search query is invalid: ") + msg) {}

FileRemoverException::FileRemoverException(const std::string& file) : BasicException(std::string("File remove is invalid: ") + file) {}

JsonException::JsonException() : BasicException("JSON error!") {}

PlaylistException::PlaylistException(const std::string& name) : BasicException(std::string("Error creating playlist: ") + name) {}

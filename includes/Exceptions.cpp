#include "Exceptions.h"

SearchException::SearchException(const std::string& msg) : BasicException("Search query is invalid: " + msg) {}

FileRemoverException::FileRemoverException(const std::string& file) : BasicException("File remove is invalid: " + file) {}

JsonException::JsonException() : BasicException("JSON error!") {}

PlaylistException::PlaylistException(const std::string& name) : BasicException("Error creating playlist: " + name) {}

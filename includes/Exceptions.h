#pragma once

#include <stdexcept>
#include <string>

class BasicException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class SearchException : public BasicException {
public:
    explicit SearchException(const std::string& msg);
};

class FileRemoverException : public BasicException {
public:
    explicit FileRemoverException(const std::string& file);
};

class JsonException : public BasicException {
public:
    JsonException();
};

class PlaylistException : public BasicException {
public:
    explicit PlaylistException(const std::string& name);
};

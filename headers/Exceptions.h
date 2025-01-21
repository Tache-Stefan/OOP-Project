#pragma once

#include <stdexcept>
#include <string>

class BasicException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class FileRemoverException : public BasicException {
public:
    explicit FileRemoverException(const std::string& file);
};

class FileException : public BasicException {
public:
    explicit FileException(const std::string& file);
};

class JsonException : public BasicException {
public:
    JsonException();
};

class EnvironmentException : public BasicException {
public:
    using BasicException::BasicException;
};

#include "../headers/Exceptions.h"

FileRemoverException::FileRemoverException(const std::string& file) : BasicException(std::string("File remove is invalid: ") + file) {}

FileException::FileException(const std::string& file) : BasicException(std::string("File not found: ") + file) {}

JsonException::JsonException() : BasicException("JSON error!") {}

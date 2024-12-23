#pragma once
#include <unordered_map>
#include <string>
#include <memory>

template<class T>
class Collection {
private:
    static std::unordered_map<std::string, std::shared_ptr<T>> itemMap;
public:
    static void addItem(const std::shared_ptr<T>& item);
    static std::shared_ptr<T> getItem(const std::string& id);
};

#include "../src/Collection.cpp"

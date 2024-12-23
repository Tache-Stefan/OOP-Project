#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

template<class T>
std::unordered_map<std::string, std::shared_ptr<T>> Collection<T>::itemMap;

template<class T>
void Collection<T>::addItem(const std::shared_ptr<T>& item) {
    itemMap[item->getID()] = item;
    std::cout << "Added \"" << item->getTitle() << "\" to the collection." << std::endl;
}

template<class T>
std::shared_ptr<T> Collection<T>::getItem(const std::string& id) {
    const auto it = itemMap.find(id);
    if (it != itemMap.end()) {
        return it->second;
    }
    return nullptr;
}

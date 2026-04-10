#include "store.h"
#include <mutex>

void KeyValueStore::set(const std::string& key, const std::string& value) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    data[key] = value;
}

std::string KeyValueStore::get(const std::string& key) {
    std::shared_lock<std::shared_mutex> lock(mutex);
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    return "NULL";
}

bool KeyValueStore::del(const std::string& key) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    return data.erase(key) > 0;
}

size_t KeyValueStore::count() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return data.size();
}
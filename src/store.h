#ifndef STORE_H
#define STORE_H

#include <string>
#include <unordered_map>
#include <shared_mutex>

class KeyValueStore {
private:
    std::unordered_map<std::string, std::string> data;
    mutable std::shared_mutex mutex;

public:
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    bool del(const std::string& key);
    size_t count() const;
};

#endif
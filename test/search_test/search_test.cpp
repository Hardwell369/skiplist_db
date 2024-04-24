// file name: search_test.cpp
// introduction: this file is used to test the search function of skiplist

#include <iostream>

#include "../../include/include.h"

int main() {
    skiplist_db::SkipList skiplist(16);
    skiplist_db::Status status;

    std::string key = "a";
    std::vector<std::string> keys;
    std::string value = "xxx";
    skiplist_db::value_t value_get;

    keys.push_back(key);
    for (int i=1; i < 26; ++i) {
        key[0] += 1;
        keys.push_back(keys.back() + key);
        // std::cout << keys[i] << "\n";
    }

    for (auto& k : keys) {
        status = skiplist.insert(k, value);
        std::cout << status.what() << "\n";
    }

    for (auto& k : keys) {
        
        status = skiplist.search(k, value_get);
        if (status.ok()) {
            std::cout << "search key: " << k << " value: " << value_get << "\n";
        } else {
            std::cout << status.what() << "\n";
        }
    }

    status = skiplist.search("not exist key", value_get);
    if (status.ok()) {
        std::cout << "search key: " << "not exist key" << " value: " << value_get << "\n";
    } else {
        std::cout << status.what() << "\n";
    }

    return 0;
}
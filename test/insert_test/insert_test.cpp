// file name: insert_test.cpp
// introduction: this file is used to test the insert function of skiplist

#include <iostream>

#include "../../include/include.h"

int main() {
    skiplist_db::SkipList skiplist(16);
    skiplist_db::Status status;

    std::string key = "a";
    std::vector<std::string> keys;
    std::string value = "xxx";

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
        status = skiplist.insert(k, value);
        std::cout << status.what() << "\n";
    }

    skiplist.display();

    return 0;
}
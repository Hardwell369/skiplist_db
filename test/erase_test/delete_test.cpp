// file name: delete_test.cpp
// introduction: this file is used to test the delete function of skiplist

#include <iostream>

#include "../../include/include.h"

int main() {
    skiplist_db::SkipList skiplist(64);
    skiplist_db::Status status;

    std::string key = "a";
    std::vector<std::string> keys;
    std::vector<std::string> delete_keys;
    std::string value = "xxx";

    keys.push_back(key);
    for (int i=1; i<10; ++i) {
        key[0] += 1;
        keys.push_back(keys.back() + key);
        // std::cout << keys[i] << "\n";
    }

    for (auto& k : keys) {
        status = skiplist.insert(k, value);
        std::cout << status.what() << "\n";
    }

    skiplist.display();

    delete_keys.push_back(keys[0]);
    delete_keys.push_back(keys[2]);
    delete_keys.push_back(keys[4]);
    for (auto k : delete_keys) {
        status = skiplist.erase(k);
        std::cout << status.what() << "\n";
    }

    skiplist.display();

    return 0;
}
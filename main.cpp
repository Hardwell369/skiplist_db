// file name: main.cpp
// introduction: this file is an example of how to use skiplist

#include <iostream>

#include "include/include.h"

int main() {
    skiplist_db::SkipList skiplist(16);
    skiplist_db::Status status;
    std::string value_get;

    std::vector<std::pair<std::string, std::string>> key_value_pairs = {
        {"a", "xxx"},
        {"b", "yyy"},
        {"c", "zzz"},
        {"d", "www"},
        {"e", "vvv"},
        {"f", "uuu"},
        {"g", "ttt"},
        {"h", "sss"},
        {"i", "rrr"},
        {"j", "qqq"},
        {"k", "ppp"},
        {"l", "ooo"},
        {"m", "nnn"},
        {"n", "mmm"},
        {"o", "lll"},
    };

    for (auto& kv : key_value_pairs) {
        status = skiplist.insert(kv.first, kv.second);
        std::cout << status.what() << "\n";
    }

    skiplist.display();

    status = skiplist.delete_node("a");
    std::cout << status.what() << "\n";

    status = skiplist.delete_node("c");
    std::cout << status.what() << "\n";

    status = skiplist.search("b", value_get);
    std::cout << status.what() << "\n";

    status = skiplist.search("c", value_get);
    std::cout << status.what() << "\n";

    skiplist.display();

    return 0;
}
// file name: node.h
// introduction: this file defines the class of node in the skiplist

#pragma once
#include <string>
#include <memory>

#include "./slice.h"

namespace skiplist_db {
class Node;
using value_t = std::string; // temp
using Nodeptr = std::shared_ptr<Node>; // temp

struct Node {
    Node() : key_(""), value_(""), right_(nullptr), down_(nullptr) {};
    Node(const Slice& key, const value_t& value) : key_(key), value_(value), right_(nullptr), down_(nullptr) {}
    ~Node() = default;

    Slice key_;
    value_t value_;
    Nodeptr right_;
    Nodeptr down_;
};
}  // namespace skiplist_db
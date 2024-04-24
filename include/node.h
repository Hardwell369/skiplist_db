// file name: node.h
// introduction: this file defines the class of node in the skiplist

#pragma once
#include <string>
#include <memory>

#include "./slice.h"

namespace skiplist_db {
class Node;
using value_t = std::string; // temp
using next_t = std::shared_ptr<Node>; // temp

class Node {
public:
    Node() : key_(""), value_(""), level_(0), next_(nullptr) {};
    Node(size_t level) : key_(""), value_(""), level_(level), next_(nullptr) {}
    Node(const Slice& key, const value_t& value, size_t level) : key_(key), value_(value), level_(level), next_(nullptr) {}
    ~Node() = default;

    const Slice& key() const { return key_; }
    const value_t& value() const { return value_; }
    size_t level() const { return level_; }

    void set_key(const Slice& key) { key_ = key; }
    void set_value(const value_t& value) { value_ = value; }

    next_t Next() { return next_; }
    void set_next(next_t next) { next_ = next; }

private:
    Slice key_;
    value_t value_;
    size_t level_;
    next_t next_;
};
}  // namespace skiplist_db
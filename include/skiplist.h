// file name: skiplist.h
// introduction: this file defines the class of skiplist

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <mutex>
#include <random>
#include <time.h>

#include "./node.h"
#include "./status.h"

namespace skiplist_db {
using Reader = std::ifstream; // temp
using Writer = std::ofstream; // temp

struct Mutexguard {
    std::mutex mtx_;
    Mutexguard() {
        mtx_.lock();
    }

    ~Mutexguard() {
        mtx_.unlock();
    }
};

class SkipList {
public:
    SkipList(size_t max_level) : max_level_(max_level), level_(0), size_(0) {
        srand((unsigned)time(NULL)); 
        head_.resize(max_level_+1);
        for (size_t i = 0; i <= max_level_; ++i) {
            head_[i] = std::make_shared<Node>(max_level);
        }
    }

    Status insert(const Slice& key, const value_t& value);
    Status delete_node(const Slice& key);
    Status search(const Slice& key, value_t& value);
    Status display();

private:
    size_t get_random_level() {
        size_t level = 1;
        while (rand() % 2) {
            ++level;
        }
        return level < max_level_ ? level : max_level_;
    }

private:
    size_t max_level_; // max level of the skiplist
    size_t level_; // current level of the skiplist 
    std::vector<std::shared_ptr<Node>> head_; // head node of the skiplist is a dummy node
    Reader reader_; 
    Writer writer_;  
    size_t size_; // current number of nodes in the skiplist
};
}  // namespace skiplist_db
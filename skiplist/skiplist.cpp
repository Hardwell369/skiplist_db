// file name: skiplist.cpp
// introduction: this file implements the class of skiplist

#include "../include/skiplist.h"

namespace skiplist_db {
    Status SkipList::insert(const Slice& key, const value_t& value) {
        std::vector<std::shared_ptr<Node>> update(max_level_+1);
        Status status;
        std::mutex mtx;
        mtx.lock();

        for (size_t i = 0; i <= level_; ++i) {
            auto current_node = head_[i];
            while (current_node->Next() != nullptr && current_node->Next()->key().compare(key) < 0) {
                current_node = current_node->Next();
            }
            update[i] = current_node;
        }

        auto current_node = update[0]->Next();
        if (current_node != nullptr && current_node->key().compare(key) == 0) {
            status.set_key_exists(key);
            return status;
        }

        size_t new_level = get_random_level();
        if (new_level > level_) {
            for (size_t i = level_+1; i <= new_level; ++i) {
                update[i] = head_[i];
            }
            level_ = new_level;
        }

        for (size_t i = 0; i <= level_; ++i) {
            auto new_node = std::make_shared<Node>(key, value, level_);
            new_node->set_next(update[i]->Next());
            update[i]->set_next(new_node);
        }

        ++size_;
        mtx.unlock();
        return status;
    }

    Status SkipList::delete_node(const Slice& key) {
        std::vector<std::shared_ptr<Node>> update(max_level_+1);
        Status status;
        std::mutex mtx;
        mtx.lock();

        for (size_t i = 0; i <= level_; ++i) {
            auto current_node = head_[i];
            while (current_node->Next() != nullptr && current_node->Next()->key().compare(key) < 0) {
                current_node = current_node->Next();
            }
            update[i] = current_node;
        }

        auto current_node = update[0]->Next();
        if (current_node == nullptr || current_node->key().compare(key) != 0) {
            status.set_not_found(key);
            return status;
        }

        for (size_t i = 0; i <= level_; ++i) {
            if (update[i]->Next() != nullptr && update[i]->Next()->key().compare(key) == 0) {
                update[i]->set_next(update[i]->Next()->Next());
            }
        }

        --size_;
        mtx.unlock();
        return status;
    }

    Status SkipList::search(const Slice& key, value_t& value) {
        Status status;
        std::mutex mtx;
        mtx.lock();

        auto current_node = head_[0]->Next();
        while (current_node != nullptr && current_node->key().compare(key) < 0) {
            current_node = current_node->Next();
        }

        if (current_node == nullptr || current_node->key().compare(key) != 0) {
            status.set_not_found(key);
            return status;
        }

        value = current_node->value();
        mtx.unlock();
        return status;
    }

    Status SkipList::display() {
        Status status;
        std::mutex mtx;
        mtx.lock();
        for (size_t i = 0; i <= level_; ++i) {
            auto current_node = head_[i]->Next();
            std::cout << "level " << i << ": ";
            while (current_node != nullptr) {
                std::cout << current_node->key().ToString() << "->" << current_node->value() << " ";
                current_node = current_node->Next();
            }
            std::cout << std::endl;
        }
        mtx.unlock();
        return status;
    }
}; // namespace skiplist_db
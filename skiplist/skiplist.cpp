// file name: skiplist.cpp
// introduction: this file implements the class of skiplist

#include "../include/skiplist.h"

namespace skiplist_db {
    Status SkipList::insert(const Slice& key, const value_t& value) {
        std::vector<Nodeptr> update;
        Status status;
        Mutexguard mtx;

        auto current_node = head_;
        while (current_node) {
            while (current_node->right_ && current_node->right_->key_.compare(key) < 0) {
                current_node = current_node->right_;
            }
            if (current_node->right_ && current_node->right_->key_.compare(key) == 0) {
                status.set_key_exists(key);
                return status;
            }
            update.emplace_back(current_node);
            current_node = current_node->down_;
        }

        bool insert = true;
        while (insert && update.size() > 0) {
            auto update_node = update.back();
            update.pop_back();
            auto new_node = std::make_shared<Node>(key, value);
            new_node->right_ = update_node->right_;
            update_node->right_ = new_node;
            new_node->down_ = nullptr;
            insert = rand() % 2;
        }

        if (insert && level_ < max_level_) {
            auto new_node = std::make_shared<Node>();
            new_node->right_ = nullptr;
            new_node->down_ = head_;
            head_ = new_node;
            ++level_;
        }
        ++size_;
        return status;
    }

    Status SkipList::erase(const Slice& key) {
        std::vector<Nodeptr> update(max_level_+1);
        Status status;
        Mutexguard mtx;

        status.set_not_found(key);
        auto current_node = head_;
        while (current_node) {
            while (current_node->right_ && current_node->right_->key_.compare(key) < 0) {
                current_node = current_node->right_;
            }
            if (current_node->right_ && current_node->right_->key_.compare(key) == 0) {
                auto delete_node = current_node->right_;
                current_node->right_ = delete_node->right_;
                delete_node->right_ = nullptr;
                delete_node->down_ = nullptr;
                delete_node.reset();
                status.set_ok();
                break;
            }
            current_node = current_node->down_;
        }

        --size_;
        return status;
    }

    Status SkipList::search(const Slice& key, value_t& value) {
        Status status;
        Mutexguard mtx;        

        auto current_node = head_;
        while (current_node) {
            while (current_node->right_ && current_node->right_->key_.compare(key) < 0) {
                current_node = current_node->right_;
            }
            if (current_node->right_ && current_node->right_->key_.compare(key) == 0) {
                value = current_node->right_->value_;
                status.set_ok();
                return status;
            }
            current_node = current_node->down_;
        }
        status.set_not_found(key);
        return status;
    }

    Status SkipList::display() {
        Status status;
        Mutexguard mtx;

        auto current_node = head_;
        auto level = level_;
        while (current_node) {
            auto temp = current_node;
            std::cout << "level " << level << ": ";
            --level;
            while (temp) {
                std::cout << temp->key_.data() << " ";
                temp = temp->right_;
            }
            std::cout << std::endl;
            current_node = current_node->down_;
        }

        return status;
    }
}; // namespace skiplist_db
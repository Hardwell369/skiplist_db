// file name: slice.h
// introduction: this file defines the class of slice as a basic data structure, used as key type

#pragma once
#include <cassert>
#include <cstddef>
#include <cstring>
#include <string>

namespace skiplist_db {
class Slice {
public:
    Slice () : data_(""), size_(0) {}
    Slice (const char* d, size_t n) : data_(d), size_(n) {}
    Slice (const std::string& s) : data_(s.data()), size_(s.size()) {}
    Slice (const char* s) : data_(s), size_(strlen(s)) {}

    Slice(const Slice&) = default;
    Slice& operator=(const Slice&) = default;

    const char* data() const { return data_; }
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    char operator[](size_t n) const {
        assert(n < size());
        return data_[n];
    }

    void clear() {
        data_ = "";
        size_ = 0;
    }

    void remove_prefix(size_t n) {
        assert(n <= size());
        data_ += n;
        size_ -= n;
    }

    std::string ToString() const { return std::string(data_, size_); }

    // Three-way comparison. Returns value:
    // < 0 if "*this" < "b",
    // == 0 if "*this" == "b",
    // > 0 if "*this" > "b"
    int compare(const Slice& b) const;

    // Return true if "x" is a prefix of "*this"
    bool starts_with(const Slice& x) const {
        return ((size_ >= x.size_) && (memcmp(data_, x.data_, x.size_) == 0));
    }

private:
    const char* data_; // pointer to the beginning of the referenced data
    size_t size_; // length (in bytes) of the referenced data
};

inline bool operator==(const Slice& x, const Slice& y) {
    return ((x.size() == y.size()) && (memcmp(x.data(), y.data(), x.size()) == 0));
}

inline bool operator!=(const Slice& x, const Slice& y) { return !(x == y); }

inline int Slice::compare(const Slice& b) const {
    const size_t min_len = (size_ < b.size_) ? size_ : b.size_;
    int r = memcmp(data_, b.data_, min_len);
    if (r == 0) {
        if (size_ < b.size_) {
            r = -1;
        } else if (size_ > b.size_) {
            r = +1;
        }
    }
    return r;
}

}; // namespace skiplist_db
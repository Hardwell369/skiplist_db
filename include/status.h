// file name: status.h
// introduction: this file defines the class of status as a basic data structure, used as return type

#pragma once
#include <string>

#include "./slice.h"

namespace skiplist_db {
class Status {
public:
    Status() : code_(Ok) {}
    ~Status() = default;

    bool ok() const { return code_ == Ok; }
    void set_ok() { code_ = Ok; }
    void set_not_found(const Slice& key) { 
        code_ = NotFound; 
        key_ = key;
    }
    void set_corruption() { code_ = Corruption; }
    void set_not_supported() { code_ = NotSupported; }
    void set_invalid_argument() { code_ = InvalidArgument; }
    void set_io_error() { code_ = IOError; }
    void set_key_exists(const Slice& key) { 
        code_ = KeyExists; 
        key_ = key;
    }

    std::string what() {
        std::string msg;
        switch (code_) {
            case Ok: msg = "OK"; break;
            case NotFound: msg = "Not found: " + key_.ToString(); break;
            case Corruption: msg = "Corruption: "; break;
            case NotSupported: msg = "Not supported: "; break;
            case InvalidArgument: msg = "Invalid argument: "; break;
            case IOError: msg = "IO error: "; break;
            case KeyExists: msg = "Key exists: " + key_.ToString(); break;
        }
        return msg;
    }

private:
    enum Code {
        Ok = 0,
        NotFound = 1,
        Corruption = 2,
        NotSupported = 3,
        InvalidArgument = 4,
        IOError = 5,
        KeyExists = 6,
    };

    Code code_;
    Slice key_;  // used in NotFound and KeyExists
};
}; // namespace skiplist_db
//
// Created by tsukuto on 02.04.19.
//

#ifndef SAKU_FILEOBJECT_H
#define SAKU_FILEOBJECT_H

#include "Object.h"
#include <array>
#include <exception>

namespace Calc {

    class FileNotFound : public std::exception {
    public:
        explicit FileNotFound(std::string what) : what_(std::move(what)) {}

        const char* what() const noexcept override { return what_.c_str(); }
    private:
        std::string what_;
    };

    class FileObject : public Object {
    public:
        explicit FileObject(std::string path);

        const std::string& GetExtension() const { return extension_; }

        const std::string& GetPath() const { return path_; }

        std::ostream& operator<<(std::ostream& output) const override {
            return output << extension_ << ":" << path_;
        }
    private:
        std::string path_;
        std::string extension_;
    };
}


#endif //SAKU_FILEOBJECT_H

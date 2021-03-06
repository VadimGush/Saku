#ifndef SAKU_OBJECT_H
#define SAKU_OBJECT_H

#include <iostream>
#include <type_traits>
#include <fstream>
#include <vector>
#include <memory>

namespace Calc {
    enum class ObjectType {
        NUMBER, STRING, VECTOR, VALUE, FILE
    };

    std::ostream &operator<<(std::ostream &, ObjectType);

    class Object {
    public:
        explicit Object(ObjectType type) : type_(type) {}

        ObjectType GetType() const { return type_; }

        // Возвращает размер используемых объектом данных в байтах
        virtual size_t size() const noexcept = 0;

        // Вычисление хеша для сравнения объектов в кеше
        virtual size_t hash() const noexcept = 0;

        virtual std::ostream &operator<<(std::ostream &) const = 0;

    private:
        ObjectType type_;
    };

    class NumberObject : public Object {
    public:
        explicit NumberObject(double number) : Object(ObjectType::NUMBER), number_(number), hash_(std::hash<double>{}(number)) {}

        double GetValue() const noexcept { return number_; }

        void PutValue(double value) noexcept { number_ = value; hash_ = std::hash<double>{}(value); }

        size_t size() const noexcept override { return sizeof(double); }

        size_t hash() const noexcept override { return hash_; }

        std::ostream &operator<<(std::ostream &output) const override {
            return output << number_;
        }

    private:
        size_t hash_;
        double number_;
    };

    class StringObject : public Object {
    public:
        explicit StringObject(std::string value) : Object(ObjectType::STRING),
        hash_(std::hash<std::string>{}(value)), value_(std::move(value)) {}

        const std::string &GetValue() const noexcept { return value_; }

        void PutValue(const std::string &value) noexcept {
            value_ = value;
            hash_ = std::hash<std::string>{}(value);
        }

        size_t size() const noexcept override { return value_.length(); }

        size_t hash() const noexcept override { return hash_; }

        std::ostream &operator<<(std::ostream &output) const override {
            return output << "\"" << value_ << "\"";
        }

    private:
        size_t hash_;
        std::string value_;
    };

    class VectorObject : public Object {
    public:
        VectorObject() : Object(ObjectType::VECTOR) {}

        VectorObject(std::initializer_list<std::shared_ptr<Calc::Object>> list) : Object(ObjectType::VECTOR) {
            size_ = 0;
            hash_ = 0;
            for (const auto &element : list) {
                size_ += element->size();
                hash_ += element->hash();
                objects_.push_back(element);
            }
        }

        void Put(const std::shared_ptr<Calc::Object>& object) {
            hash_ += object->hash();
            objects_.push_back(object);
        }

        unsigned long GetSize() const noexcept {
            return objects_.size();
        }

        std::shared_ptr<Calc::Object> Get(int id) {
            return objects_.at(id);
        }

        size_t size() const noexcept override { return size_; }

        size_t hash() const noexcept override { return hash_; }

        std::ostream &operator<<(std::ostream &output) const override {
            output << "[ ";
            bool first = true;
            for (const auto &element : objects_) {
                if (!first) output << ", ";
                element->operator<<(output);
                first = false;
            }
            return output << " ]";
        }

    private:
        std::vector<std::shared_ptr<Calc::Object>> objects_;
        size_t size_;
        size_t hash_;
    };

    class ValueObject : public Object {
    public:
        ValueObject(std::string name, double value) : Object(ObjectType::VALUE), name_(std::move(name)), value_(value) {
            hash_ = std::hash<std::string>{}(name_) + std::hash<double>{}(value_);
        }

        const std::string &GetName() const { return name_; }

        double GetValue() const { return value_; }

        void PutValue(double value) noexcept {
            value_ = value;
            hash_ = std::hash<std::string>{}(name_) + std::hash<double>{}(value_);
        }

        size_t size() const noexcept override { return name_.length() + sizeof(double); }

        size_t hash() const noexcept override { return hash_; }

        std::ostream &operator<<(std::ostream &output) const override {
            return output << "{ " << name_ << " : " << value_ << " }";
        }

    private:
        size_t hash_;
        std::string name_;
        double value_;
    };

    struct InvalidArgument : public std::exception {
        const char* what() const noexcept override { return "Неверный тип аргумента"; }
    private:
    };

    template<typename T>
    std::shared_ptr<T> downcast(std::shared_ptr<Object> arg, ObjectType type) {
        if (arg->GetType() == type) {
            return std::dynamic_pointer_cast<T>(arg);
        } else throw InvalidArgument();
    }

}


#endif //SAKU_OBJECT_H

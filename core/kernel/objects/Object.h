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

        virtual std::ostream &operator<<(std::ostream &) const = 0;

    private:
        ObjectType type_;
    };

    template<
            typename T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class NumberObject : public Object {
    public:
        explicit NumberObject(T number) : Object(ObjectType::NUMBER), number_(number) {}

        T GetValue() const noexcept { return number_; }

        void PutValue(T value) noexcept { number_ = value; }

        std::ostream &operator<<(std::ostream &output) const override {
            return output << number_;
        }

    private:
        T number_;
    };

    class StringObject : public Object {
    public:
        explicit StringObject(std::string value) : Object(ObjectType::STRING), value_(std::move(value)) {}

        const std::string &GetValue() const noexcept { return value_; }

        void PutValue(const std::string &value) noexcept { value_ = value; }

        std::ostream &operator<<(std::ostream &output) const override {
            return output << "\"" << value_ << "\"";
        }

    private:
        std::string value_;
    };

    class VectorObject : public Object {
    public:
        VectorObject() : Object(ObjectType::VECTOR) {}

        VectorObject(std::initializer_list<std::shared_ptr<Calc::Object>> list) : Object(ObjectType::VECTOR) {
            for (const auto &element : list) {
                objects_.push_back(element);
            }
        }

        std::vector<std::shared_ptr<Calc::Object>> &GetVector() {
            return objects_;
        }

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
    };

    template<
            typename T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class ValueObject : public Object {
    public:
        ValueObject(std::string name, T value) : Object(ObjectType::VALUE), name_(std::move(name)), value_(value) {}

        const std::string &GetName() const { return name_; }

        T GetValue() const { return value_; }

        void PutValue(T value) noexcept { value_ = value; }

        std::ostream &operator<<(std::ostream &output) const override {
            return output << "{ " << name_ << " : " << value_ << " }";
        }

    private:
        std::string name_;
        T value_;
    };

}


#endif //SAKU_OBJECT_H

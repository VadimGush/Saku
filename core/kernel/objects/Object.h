#ifndef SAKU_OBJECT_H
#define SAKU_OBJECT_H

#include <iostream>

namespace Calc {
    enum class ObjectType {};

    class Object {
    public:
        Object(ObjectType type) : type_(type) {}

        virtual ObjectType GetType() const =0;

        virtual std::ostream& operator<<(std::ostream&) const =0;
    private:
        ObjectType type_;
    };

}

#endif //SAKU_OBJECT_H

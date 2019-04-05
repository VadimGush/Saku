//
// Created by tsukuto on 05.04.19.
//


#include "Object.h"

std::ostream& Calc::operator<<(std::ostream& output, Calc::ObjectType input) {
    switch(input) {
        case Calc::ObjectType::FILE: output << "file"; break;
        case Calc::ObjectType::NUMBER: output << "number"; break;
        case Calc::ObjectType::VECTOR: output << "vector"; break;
        case Calc::ObjectType::VALUE: output << "value"; break;
        case Calc::ObjectType::STRING: output << "string"; break;
    }
    return output;
}

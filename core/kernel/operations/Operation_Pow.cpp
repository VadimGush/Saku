#include "Operation_Pow.h"
#include <cmath>

using namespace Calc;

void Operation_Pow::init(std::shared_ptr<Calc::Object> args) {
    // TODO: Здесь мы дожны по хорошему выдать нормальное исключение с пояснениеями, а не то
    // TODO: , что может выдать нам downcast
    auto vec = downcast<VectorObject>(args, ObjectType::VECTOR);

    if (vec->GetVector().size() == 2) {

        auto first_argument = downcast<NumberObject>(vec->GetVector()[0], ObjectType::NUMBER);
        auto second_argument = downcast<NumberObject>(vec->GetVector()[1], ObjectType::NUMBER);

        base_ = first_argument->GetValue();
        power_ = second_argument->GetValue();

    } else throw InvalidArguments("pow", 2);
}

std::unique_ptr<Calc::Object> Operation_Pow::Calculate(RuntimePlatform &platform) {
    return std::make_unique<Calc::NumberObject>(pow(base_, power_));
}
#include "Operation_Pow.h"
#include <cmath>

using namespace Calc;

Operation_Pow::Operation_Pow(double base, double power) : base_(base), power_(power) {}

std::shared_ptr<Calc::Object> Operation_Pow::Calculate(RuntimePlatform& platform) {
    return std::make_shared<Calc::NumberObject<double>>(pow(base_, power_));
}
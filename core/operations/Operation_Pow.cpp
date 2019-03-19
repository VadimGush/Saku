//
// Created by tsukuto on 18.03.19.
//

#include "Operation_Pow.h"
#include <cmath>

using namespace Calc;

Operation_Pow::Operation_Pow(double base, double power) : base_(base), power_(power) {}

void Operation_Pow::Calculate(RuntimePlatform& platform, std::ostream& output) {
    output << "Ответ: " << pow(base_, power_) << std::endl;
}
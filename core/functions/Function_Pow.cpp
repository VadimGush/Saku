//
// Created by tsukuto on 18.03.19.
//

#include "Function_Pow.h"
#include <cmath>

using namespace Calc;

Function_Pow::Function_Pow(double base, double power) : base_(base), power_(power) {}

void Function_Pow::Calculate(RuntimePlatform& platform, std::ostream& output) {
    output << "Ответ: " << pow(base_, power_) << std::endl;
}
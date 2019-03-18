//
// Created by tsukuto on 18.03.19.
//

#include "RuntimePlatform.h"
using namespace Calc;


void Calc::RuntimePlatform::Handle(Function &function, std::ostream &output) {
    function.Calculate(*this, output);
}
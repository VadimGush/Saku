//
// Created by tsukuto on 26.03.19.
//

#include "Operation_Integral.h"

using namespace Calc;

Operation_Integral::Operation_Integral(std::shared_ptr<function_type> function, double a, double b) : function_{std::move(function)}, range_{a, b} {}

void Operation_Integral::Calculate(RuntimePlatform&, std::ostream& output) {
    // TODO: Переписать под многопоточный процессор
    double h = (range_.first - range_.second) / n_;
    double sum = 0;
    double xi;
    for (int i = 1; i <= n_; i++) {
        xi = range_.first + h*i;
        sum += (*function_)(xi) + 4*(*function_)(xi - h/2) + (*function_)(range_.first + (h*(i-1)));
    }
    output << "Integral = " << sum * h/6 << std::endl;
}



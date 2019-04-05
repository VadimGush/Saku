#include "Operation_Integral.h"

using namespace Calc;

Operation_Integral::Operation_Integral(function_type &function, double a, double b) : function_{function},
                                                                                      range_{a, b} {}

std::unique_ptr<Calc::Object> Operation_Integral::Calculate(RuntimePlatform &) {
    // TODO: Переписать под многопоточный процессор
    double h = (range_.first - range_.second) / n_;
    double sum = 0;
    double xi;
    for (int i = 1; i <= n_; i++) {
        xi = range_.first + h * i;
        sum += function_(xi) + 4 * function_(xi - h / 2) + function_(range_.first + (h * (i - 1)));
    }
    return std::make_unique<Calc::NumberObject<double>>(sum);
}



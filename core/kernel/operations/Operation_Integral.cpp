#include "Operation_Integral.h"

using namespace Calc;

Operation_Integral::Operation_Integral(const std::shared_ptr<Calc::Object>& args) {

}

std::unique_ptr<Calc::Object> Operation_Integral::Calculate() {
    // TODO: Переписать под многопоточный процессор
    /*
    double h = (range_.first - range_.second) / n_;
    double sum = 0;
    double xi;
    for (int i = 1; i <= n_; i++) {
        xi = range_.first + h * i;
        sum += function_(xi) + 4 * function_(xi - h / 2) + function_(range_.first + (h * (i - 1)));
    }
    return std::make_unique<Calc::NumberObject<double>>(sum);
     */
    return nullptr;
}



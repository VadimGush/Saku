#ifndef SAKU_RESULT_H
#define SAKU_RESULT_H

namespace Calc {
    // Типы операций
    enum class ResultType { DOUBLE, VECTOR };

    // Result - оболочка для результата выполнения некоторой операции
    class Result {
    public:
        ResultType GetType() { return type_; }
    protected:
        explicit Result(ResultType type) : type_{type} {}
    private:
        ResultType type_;
    };
    

}

#endif //SAKU_RESULT_H

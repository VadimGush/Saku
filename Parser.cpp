//
// Created by tsukuto on 02.04.19.
//

#include "Parser.h"
#include "algorithm"

using namespace std;

// Удаляет пробелы везде, но не внутри кавычек
void Calc::remove_spaces(string& input) {
    bool quotation = false;
    input.erase(remove_if(input.begin(), input.end(), [&](auto symbol){
        if (symbol == '\"') quotation = (!quotation);
        return quotation? false : symbol == ' ';
    }), input.end());
}

// Является ли символ частью допустимого имени переменной или функции
bool Calc::isvar(char symbol) noexcept { return isalpha(symbol) || symbol == '_'; }

// Парсим выражение
shared_ptr<Calc::Object> Calc::parse(string::iterator begin, string::iterator end) {

    if (begin == end) throw ParserException("пустое выражение");

    // Создаём локальную временную переменную
    shared_ptr<Calc::Object> var;

    // Получаем первый токен
    auto first_token = find_if(begin, end, [](auto symbol) { return !isvar(symbol); });



    // Возвращаем переменную
    return var;
}



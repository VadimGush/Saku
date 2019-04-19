#ifndef CALC_KERNEL_H
#define CALC_KERNEL_H

#include <memory>
#include <vector>
#include <map>
#include "Platform.h"
#include "objects/Object.h"
#include "operations/Operation.h"

namespace Calc {

    struct FunctionNotFound : public std::exception {

        explicit FunctionNotFound(std::string what) : what_(std::move(what)) {}

        const char* what() const noexcept override {
            return what_.c_str();
        }
    private:
        std::string what_;
    };

    // Kernel (ядро) инициализирует платформы и хранит все локальные переменные.
    class Kernel {
    public:

        static std::shared_ptr<Kernel> Instance();

        // Список платформ
        const std::vector<std::shared_ptr<Platform>> &GetPlatforms() const { return platforms_; }

        // Текущая платформа
        std::shared_ptr<Platform> GetPlatform() const { return current_platform_; }

        // Смена платформы
        void SetPlatform(unsigned long id) { current_platform_ = platforms_.at(id); }

        // Получить переменную по её имени
        std::shared_ptr<Calc::Object> GetVariable(const std::string &name) const {
            return variables_.at(name);
        }

        // Получить список переменных
        const std::map<std::string, std::shared_ptr<Calc::Object>> &GetVariables() const {
            return variables_;
        }

        // Устанавливает новое значение переменной если таковая имеется, если нет, то создаёт новую
        // с переданным значением
        void AssignVariable(const std::string &name, std::shared_ptr<Calc::Object> object) {
            variables_.insert_or_assign(name, object);
        }

        // Удаление переменной
        void RemoveVariable(const std::string &name) {
            variables_.erase(name);
        }

        // Вычисляет функцию на текущей платформе и возвращает результат
        std::shared_ptr<Calc::Object> Calculate(
                const std::string& function_name, const std::shared_ptr<Calc::Object>& args);

        // Включает или отключает кеширование результатов
        void SetCache(bool cache) noexcept { enable_cache_= cache; }

        // Включён ли кеш
        bool IsCache() noexcept { return enable_cache_; }

        // Размер кеша в байтах
        size_t CacheSize() const noexcept {
            size_t result = 0;
            for (const auto& element : cache_) {
                result += element.second->size();
            }
            return result;
        }

        // Количество сохранённых объектов в кеше
        unsigned long CacheLength() const noexcept {
            return cache_.size();
        }

    private:
        Kernel();

        static std::shared_ptr<Kernel> instance_;

        std::shared_ptr<Platform> current_platform_;

        std::vector<std::shared_ptr<Platform>> platforms_;

        std::map<std::string, std::shared_ptr<Calc::Object>> variables_;

        std::map<std::pair<std::string, size_t>, std::shared_ptr<Calc::Object>> cache_;

        bool enable_cache_ = true;
    };
}


#endif //CALC_KERNEL_H

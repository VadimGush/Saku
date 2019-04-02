#ifndef CALC_KERNEL_H
#define CALC_KERNEL_H

#include <memory>
#include <vector>
#include <map>
#include "Platform.h"
#include "objects/Object.h"
#include "operations/Operation.h"

namespace Calc {

    // Kernel (ядро) инициализирует платформы и хранит все локальные переменные.
    class Kernel {
    public:

        static Kernel* Instance();

        // Список платформ
        const std::vector<std::shared_ptr<Platform>>& GetPlatforms() const { return platforms_; }

        // Текущая платформа
        std::shared_ptr<Platform> GetPlatform() const { return current_platform_; }

        // Смена платформы
        void SetPlatform(unsigned long id) { current_platform_ = platforms_.at(id); }

        // Получить переменную по её имени
        std::shared_ptr<Calc::Object> GetVariable(const std::string& name) const {
            return variables_.at(name);
        }

        // Устанавливает новое значение переменной если таковая имеется, если нет, то создаёт новую
        // с переданным значением
        void AssignVariable(const std::string& name, std::shared_ptr<Calc::Object> object) {
            variables_.insert_or_assign(name, object);
        }

        // Удаление переменной
        void RemoveVariable(const std::string& name) {
             variables_.erase(name);
        }

    private:
        Kernel();

        static Kernel* instance_;

        std::shared_ptr<Platform> current_platform_;
        std::vector<std::shared_ptr<Platform>> platforms_;

        std::map<std::string, std::shared_ptr<Calc::Object>> variables_;
        
        const std::map<std::string, std::shared_ptr<Operation>> operations_;
    };
}


#endif //CALC_KERNEL_H

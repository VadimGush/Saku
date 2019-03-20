//
// Created by tsukuto on 18.03.19.
//

#ifndef CALC_KERNEL_H
#define CALC_KERNEL_H

#include <memory>
#include <vector>
#include "Platform.h"

namespace Calc {

    // Ядро содержит в себе список инициализированных платформ и одну текущую, которая
    // будет использоваться для всех вызванных вычислений
    class Kernel {
    public:
        static Kernel* Instance();

        // Список платформ
        const std::vector<std::shared_ptr<Platform>>& GetPlatforms() { return platforms_; }

        // Текущая платформа
        std::shared_ptr<Platform> GetPlatform() { return current_platform_; }

        // Смена платформы
        void SetPlatform(unsigned long id) {
            current_platform_ = platforms_.at(id);
        }

    private:
        Kernel();

        static Kernel* instance_;
        std::vector<std::shared_ptr<Platform>> platforms_;
        std::shared_ptr<Platform> current_platform_;
    };
}


#endif //CALC_KERNEL_H

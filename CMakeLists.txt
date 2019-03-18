cmake_minimum_required(VERSION 3.13)
project(Calc)

set(CMAKE_CXX_STANDARD 17)

find_library(OpenCL REQUIRED)

add_executable(Calc main.cpp core/Command.h core/CommandManager.cpp core/CommandManager.h core/Command_Help.cpp core/Command_Help.h core/Command.cpp core/kernel/Kernel.cpp core/kernel/Kernel.h core/kernel/Platform.h core/functions/Function.h core/kernel/RuntimePlatform.h core/kernel/RuntimePlatform.cpp core/Command_KernelInfo.cpp core/Command_KernelInfo.h core/functions/Function_Pow.cpp core/functions/Function_Pow.h core/Command_Pow.cpp core/Command_Pow.h core/kernel/CPUPlatform.cpp core/kernel/CPUPlatform.h)

target_link_libraries(Calc ${OpenCL_LIBRARY})


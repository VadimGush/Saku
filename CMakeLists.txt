cmake_minimum_required(VERSION 3.13)
project(Saku)

set(CMAKE_CXX_STANDARD 17)

find_library(OpenCL REQUIRED)

add_executable(Saku main.cpp core/commands/Command.h core/CommandManager.cpp core/CommandManager.h core/commands/Command_Help.cpp core/commands/Command_Help.h core/commands/Command.cpp core/kernel/Kernel.cpp core/kernel/Kernel.h core/kernel/Platform.h core/operations/Operation.h core/kernel/RuntimePlatform.h core/kernel/RuntimePlatform.cpp core/commands/Command_KernelInfo.cpp core/commands/Command_KernelInfo.h core/operations/Operation_Pow.cpp core/operations/Operation_Pow.h core/commands/Command_Pow.cpp core/commands/Command_Pow.h core/kernel/CPUPlatform.cpp core/kernel/CPUPlatform.h core/commands/Command_Settings.cpp core/commands/Command_Settings.h core/commands/Command_CalcFunction.cpp core/commands/Command_CalcFunction.h)

target_link_libraries(Saku ${OpenCL_LIBRARY})


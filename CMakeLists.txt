cmake_minimum_required(VERSION 3.13)
project(Saku VERSION 0.1.5)

set(CMAKE_CXX_STANDARD 17)

configure_file("configure.h.in" "configure.h")
include_directories(${CMAKE_BINARY_DIR})

find_library(OpenCL REQUIRED)

add_executable(Saku main.cpp core/commands/Command.h core/commands/CommandManager.cpp core/commands/CommandManager.h core/commands/Command_Help.cpp core/commands/Command_Help.h core/commands/Command.cpp core/kernel/Kernel.cpp core/kernel/Kernel.h core/kernel/Platform.h core/kernel/operations/Operation.h core/kernel/RuntimePlatform.h core/commands/Command_KernelInfo.cpp core/commands/Command_KernelInfo.h core/kernel/operations/Operation_Pow.cpp core/kernel/operations/Operation_Pow.h core/kernel/CPUPlatform.cpp core/kernel/CPUPlatform.h core/commands/Command_CalcFunction.cpp core/commands/Command_CalcFunction.h core/kernel/operations/Operation_Integral.cpp core/kernel/operations/Operation_Integral.h core/kernel/objects/Object.h Parser.cpp Parser.h core/kernel/objects/FileObject.cpp core/kernel/objects/FileObject.h core/commands/Command_Variables.cpp core/commands/Command_Variables.h core/kernel/objects/Object.cpp)

target_link_libraries(Saku ${OpenCL_LIBRARY})


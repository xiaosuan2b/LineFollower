cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME car_green)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

enable_language(CXX)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# 在链接库之前添加以下选项
target_link_options(${PROJECT_NAME} PRIVATE
    -Wl,-u,_printf_float   # 启用 printf 浮点格式化
    -Wl,-u,_sprintf_float  # 启用 sprintf 浮点格式化
    # -specs=nosys.specs
)

# 添加链接器规范
target_link_options(${PROJECT_NAME} PRIVATE
    -lstdc++ 
    --specs=nosys.specs    # 不使用简化版库
    -lc                    # 链接标准 C 库
    -lm                    # 链接数学库（若需要）
)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ./Core/Src/motor.c
    ./Core/Src/timer.c
    ./Core/Src/bluetooth.c
    ./Core/Src/state_machine.c
    ./Core/Src/follow.cpp
    ./Core/Src/IRSensor.cpp
    ./Core/Src/config.c
    ./Core/Src/pid.c
    ./Core/Src/pid_control.cpp
    ./Core/Src/OLED.c
    ./Core/Src/oled_dispaly.c
    
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)


# Convert to .hex and .bin
set(HEX_FILE ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
        Building ${BIN_FILE}")
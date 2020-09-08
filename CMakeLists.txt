cmake_minimum_required(VERSION 3.1)
project(minimu-ahrs LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(minimu-ahrs
    src/main.cpp
)

target_compile_features(minimu-ahrs PUBLIC cxx_std_17)
target_compile_options(minimu-ahrs PRIVATE
    -Wall
    -Wextra
    -Wshadow # Warn if variable overshadows parent context
    -Wnon-virtual-dtor # Warn if class with virtual func has novirt dtor
    -Wold-style-cast # Warn for c-style casts
    -Wcast-align # Warn for potential performance problem casts
    -Wunused # Warn on anything being unused
    -Woverloaded-virtual # Warn if overload a virtual function
    -Wpedantic # Warn if non-standard C++ is used
    -Wconversion # Warn on type conversions that may lose data
    -Wsign-conversion # Warn on sign conversions
    -Wdouble-promotion # Warn if float is implicit promoted to double
)

add_subdirectory(lib/kalman-ahrs)
add_subdirectory(lib/minimu)

target_link_libraries(minimu-ahrs
    ahrs::ahrs
    minimu::minimu-lib
)

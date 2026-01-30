cmake_minimum_required(VERSION 3.15...4.0)

project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

if(MSVC)
    add_compile_definitions(_USE_MATH_DEFINES)
endif()

# Force -fPIC for the qualpal library (required for shared libraries)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(qualpal 4.0 QUIET)
if(NOT qualpal_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        qualpal
        GIT_REPOSITORY https://github.com/jolars/qualpal
        GIT_TAG v4.0.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(qualpal)
endif()

pybind11_add_module(_qualpal 
    src/main.cpp 
    src/color_conversions.cpp
    src/color_distance.cpp
    src/palette_generation.cpp
)
target_link_libraries(_qualpal PRIVATE qualpal::qualpal)

install(TARGETS _qualpal DESTINATION .)

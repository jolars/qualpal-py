cmake_minimum_required(VERSION 3.15...4.0)

project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

# Add include directories if needed
include_directories(include)

pybind11_add_module(_qualpal 
    src/main.cpp
    src/qualpal/analyze.cpp
    src/qualpal/color_difference.cpp
    src/qualpal/colors.cpp
    src/qualpal/cvd.cpp
    src/qualpal/farthest_points.cpp
    src/qualpal/palettes.cpp
    src/qualpal/qualpal.cpp
    src/qualpal/validation.cpp
)

install(TARGETS _qualpal DESTINATION .)

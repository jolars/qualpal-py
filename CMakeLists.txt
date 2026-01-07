cmake_minimum_required(VERSION 3.15...4.0)

project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
find_package(OpenMP)

include(FetchContent)

# Force -fPIC for the qualpal library (required for shared libraries)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

FetchContent_Declare(
    qualpal
    GIT_REPOSITORY https://github.com/jolars/qualpal
    GIT_TAG        v3.3.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(qualpal)

# Define _USE_MATH_DEFINES for Windows (MSVC) to enable M_PI
if(MSVC)
    target_compile_definitions(qualpal PRIVATE _USE_MATH_DEFINES)
endif()

pybind11_add_module(_qualpal src/main.cpp)
target_link_libraries(_qualpal PRIVATE qualpal::qualpal)

if(OpenMP_CXX_FOUND)
    target_link_libraries(_qualpal PRIVATE OpenMP::OpenMP_CXX)
endif()

install(TARGETS _qualpal DESTINATION .)

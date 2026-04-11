cmake_minimum_required(VERSION 3.15...4.0)

project(GRIDASTAR LANGUAGES C CXX)

# cmake -B build -S . -DRAYLIB_PATH=$HOME/Documents/raylib
# cmake --build build

# emcmake cmake -B build-web -S . -DRAYLIB_PATH=$HOME/Documents/raylib
# cmake --build build-web

# cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# ------------------ Compile ------------------ #
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
#set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()

# User provides path to raylib
if(NOT RAYLIB_PATH)
    message(FATAL_ERROR "Please set -DRAYLIB_PATH=/path/to/raylib")
endif()

add_subdirectory(${RAYLIB_PATH} raylib-build)

add_executable(GRIDASTAR)

target_include_directories(GRIDASTAR PUBLIC include)

target_link_libraries(GRIDASTAR raylib)

target_compile_options(GRIDASTAR PRIVATE -g)

target_sources(GRIDASTAR PRIVATE
    source/algorithm/GridHeap.cpp
    source/algorithm/GridEnvironment.cpp
    source/algorithm/Pathfinding.cpp
    source/ui/GridUI.cpp
    source/Main.cpp
)


if(EMSCRIPTEN)
    message("Setting flags for web build...")
    set_target_properties(GRIDASTAR PROPERTIES
        LINK_FLAGS "--preload-file ../assets"
    )

    set(CMAKE_EXECUTABLE_SUFFIX ".js")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPLATFORM_WEB -sUSE_PTHREADS=1 -fexceptions")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPLATFORM_WEB -sUSE_PTHREADS=1 -fexceptions")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sUSE_PTHREADS=1 -sALLOW_MEMORY_GROWTH=1 -sASYNCIFY -sMODULARIZE=1 -sEXPORT_ES6=1 -sASSERTIONS=1 -sPTHREADS_DEBUG=1 -sPTHREAD_POOL_SIZE=2")
endif()
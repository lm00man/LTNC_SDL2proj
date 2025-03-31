cmake_minimum_required(VERSION 3.29)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(PNG REQUIRED)

add_executable(untitled2 src/game.cpp
        src/game.cpp
        include/textureManager.h
        src/textureManager.cpp
        src/main.cpp
        include/Gameobject.h
        src/gameObject.cpp
        include/Map.h
        src/Map.cpp)
target_link_libraries(untitled2
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,
        SDL2::SDL2,
        SDL2::SDL2-static>
)
target_link_libraries(untitled2 PRIVATE
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,
        SDL2_image::SDL2_image,
        SDL2_image::SDL2_image-static>)

target_link_libraries(untitled2 PRIVATE PNG::PNG)

target_include_directories(untitled2 PRIVATE include/)


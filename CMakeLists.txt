cmake_minimum_required(VERSION 3.29)
project(LTNC_SDL2proj)

set(CMAKE_CXX_STANDARD 20)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

add_executable(LTNC_SDL2proj src/game.cpp
        src/game.cpp
        include/textureManager.h
        src/textureManager.cpp
        src/main.cpp
        include/Gameobject.h
        src/gameObject.cpp
        src/main.cpp
        include/Grid.h
        src/Grid.cpp
)
target_link_libraries(LTNC_SDL2proj
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(LTNC_SDL2proj PRIVATE
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,
        SDL2_image::SDL2_image,
        SDL2_image::SDL2_image-static>)

target_link_libraries(LTNC_SDL2proj PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,
        SDL2_ttf::SDL2_ttf,
        SDL2_ttf::SDL2_ttf-static>)

target_link_libraries(LTNC_SDL2proj PRIVATE PNG::PNG)

target_include_directories(LTNC_SDL2proj PRIVATE include/)


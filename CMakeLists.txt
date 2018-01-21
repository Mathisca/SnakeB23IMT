cmake_minimum_required(VERSION 3.8)
project(b23projet)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions("/DDEBUG=1")
else ()
    add_definitions("/DDEBUG=0")
endif ()

file(GLOB_RECURSE SOURCE_FILES src/*.c src/*.h)

add_executable(b23projet ${SOURCE_FILES} src/Objects/GameObject.h)

# Copie des assets dans le dossier de build
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/bin/assets/)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Recherche des librairies SDL
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

# Link des librairies trouvées
TARGET_LINK_LIBRARIES(b23projet ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} Threads::Threads m)
cmake_minimum_required(VERSION 3.26.0)

project(zappy VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Optionnel : si raylib a besoin de math, pthread, etc. (utile sous Linux)
set(EXTRA_LIBS m pthread dl rt X11)

# SFML (si toujours utilisé ailleurs)
# find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# ⛳ Si raylib est installé dans /usr/local, ajoute manuellement include/lib dirs
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Sinon, si raylib est ajouté comme sous-projet (git submodule), garde ceci :
add_subdirectory(raylib)

# App code
add_subdirectory(app)

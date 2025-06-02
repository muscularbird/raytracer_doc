cmake_minimum_required(VERSION 3.26.0)

project(zappy VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# 👇 Ajout SFML ici
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# 👇 Ajoute raylib localement comme sous-projet
add_subdirectory(raylib)

# 👇 Compile ton code après raylib
add_subdirectory(app)


# Define source and header files
set(SOURCES
        src/main.cpp
        src/core/Game.cpp
        src/graphics/SquareComponent.cpp
        src/logs/Logger.cpp
)

set(HEADERS
        include/include.hpp
        include/core/Game.hpp
        include/graphics/SquareComponent.hpp
        include/logs/Logger.hpp
)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        /usr/local/include
)

# Set compile options for Debug and Release modes
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-g -Wall>
        $<$<CONFIG:Release>:-O3 -Wall>
)

# 👇 Lien avec SFML
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# 🔗 Lien avec la cible raylib générée par le sous-dossier
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# (Facultatif mais utile sous Linux) : ajoute libs système si non résolues automatiquement
if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl rt X11)
endif()

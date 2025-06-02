# Define source and header files
set(SOURCES
        src/main.cpp

)

set(HEADERS
        include/include.hpp

)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include gui_sfml_lib/include)

# Set compile options for Debug and Release modes
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-g -Wall>
        $<$<CONFIG:Release>:-O3 -Wall>
)

# 👇 Lien avec SFML
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# 🔗 Lien avec la cible raylib générée par le sous-dossier
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

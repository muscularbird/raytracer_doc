#include "../include/include.hpp"
#include "../include/core/Game.hpp"

void signal_handler(int signal) {
    if (signal == SIGINT) {
        std::cout << "\nTerminating...\n" << std::endl;
        std::exit(0);
    }
}

int main(const int argc, const char *const av[], const char *const env[])
{
    (void)env;
    signal(SIGINT, signal_handler);

    try {
        Game game;
        game.run(); // Gère boucle raylib + réseau + draw
        return 0;
    } catch (...) {
        std::cerr << "Erreur.\n" << std::endl;
        return 84;
    }

    return 0;
}


#include "../include/include.hpp"
#include "../include/core/Game.hpp"
#include "../include/logs/Logger.hpp"

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
        Logger::getInstance().log("demarrage", LogLevel::INFO); // info par defaut
        Game game;
        game.run(); // Gère boucle raylib + réseau + draw
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}


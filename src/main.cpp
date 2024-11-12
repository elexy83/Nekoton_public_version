#include "../include/stdafx.hpp"
#include "../include/game.hpp"


int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    game game;

    while(game.runnnig()) {
        game.update_dt();
        game.update();
        game.render();
    }
    return 0;
}
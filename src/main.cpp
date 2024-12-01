#include "../include/stdafx.hpp"
#include "../include/game.hpp"


int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    game game;

    game.run();

    return 0;
}
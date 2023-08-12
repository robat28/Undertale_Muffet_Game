#include "Game.hpp"

int main() {
    
    Game game;

    /**
     *  @brief The game loop. 
     *  One iteration is one frame of the game. 
     *  It updates the render objects and draws them every frame.
     */
    while (game.running()) {
        game.update();
        game.render();
    }

    return 0;
}

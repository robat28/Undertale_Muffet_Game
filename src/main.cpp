#include "Game.hpp"

int main(int argc, char** argv) {
    
    // Find the folder
    std::string dataDir = argv[0];
    dataDir.erase(dataDir.rfind("/"));
    dataDir.append("/../");
    Game game(dataDir);

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

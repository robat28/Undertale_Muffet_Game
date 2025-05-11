#include "cScreen.hpp"
#include "Game.hpp"

class GameScreen : public cScreen {
    private:

    std::string dataDir;
    sf::RenderWindow* window;
    bool running;

    std::unique_ptr<Game> game;

    public:

    virtual int Run();
    GameScreen(std::string dataDir, sf::RenderWindow *window);
    
};


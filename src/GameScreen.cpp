# include "GameScreen.hpp"


/**
 * Public Functions 
 */


/**
 * @brief Constructor of Gamescrenn.
 */
GameScreen::GameScreen(std::string dataDir, sf::RenderWindow *window) {
    this->dataDir = dataDir;
    this->window = window;
}


/**
 * @brief The cScreen main loop.  After losing, the game object gets destroyed. 
 */
int GameScreen::Run() {
    this->game = std::make_unique<Game>(this->dataDir, this->window);

    while(true) {
        while(const std::optional evnt = window->pollEvent()) {
            if (evnt->is<sf::Event::Closed>()) {
                return (-1);
            }
            if (const auto* keyPressed = evnt->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Escape:
                        return (-1);
                    default:
                        break;
                }
            
            }
        }

        if(this->game->switchToDFScreen) {
            return (2);
        }
        
        this->game->update();
        this->game->render();
    }

    return (-1);
}

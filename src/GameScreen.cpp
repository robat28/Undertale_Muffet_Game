# include "GameScreen.hpp"


/**
 * Private Functions 
 */


/**
 * @brief Initializes all variables of the game screen.
 */
void GameScreen::initGameScreen() {
    this->time = "";
}


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
 * @brief Getter for the time of the last game run. Used by main loop.
 */
std::string GameScreen::getTime() {
    return this->time;
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
            this->time = this->game->getFinalTime();
            return (3);
        }
        
        this->game->update();
        this->game->render();
    }

    return (-1);
}

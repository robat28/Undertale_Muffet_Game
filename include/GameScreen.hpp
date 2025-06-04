#ifndef _GAMESCREEN_
#define _GAMESCREEN_

#include "cScreen.hpp"
#include "Game.hpp"


class GameScreen : public cScreen {
    private:
    
        std::string dataDir;

        // Game objects
        sf::RenderWindow* window;
        std::unique_ptr<Game> game;

        // Time
        std::string time;

        // Initialization
        void initGameScreen();
        
        public:
        
        // Constructor 
        GameScreen(std::string dataDir, sf::RenderWindow *window);
        
        // cScreen function
        virtual int Run();

        // Getter
        std::string getTime();

};

#endif
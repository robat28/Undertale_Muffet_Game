#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game {    
    private:
        /*
            private Variables
        */
        sf::RenderWindow* window;
        sf::Event evnt;
        sf::VideoMode vMode;

        /*  Sets window as nullptr before getting initialized. More a style thing.
            @return void
        */  
        void initVariables();

        /*  Initializes the window.
            @return void
        */
        void initWindow();

    public:

        /*  Constructor
            After creating a Game instance, all variables and the window are getting intitialized. 
        */
        Game();

        /*  Destructor
            Destroys the Object after usage. 
        */
        ~Game();

        /*  Returns true, if the window is still open and returns false, if the window got closed.
            @return bool
        */
        const bool running() const;

        /*  Like a event manager. It's active while running == true and checks every frame, if one of these Events happend.
            If so do action.
            @return void
        */
        void pollEvents();

        /*  Executes the pollEvents function. Basically it the "update" of the game, by checking at the beginnig of the
            frame, if a Event happend and if so, handle it.
            @return void
        */
        void update();

        /*  Displays the window after all events got handled. display() needs to be the last function in render(), because you 
            have to make sure that all Elements of your Game are set in your window before displaying it.
            @return void
        */
        void render();
};
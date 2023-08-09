#pragma once

#include "Player.hpp"
#include "Playfield.hpp"

class Game {    
    private:
        /*
            private Variables
        */

        // Window Variables 
        sf::RenderWindow* window;
        sf::Event evnt;
        sf::VideoMode vMode;

        float playfieldCenterX;
        float playfieldCenterY;

        Player* player;

        // Playfield Variables 
        Playfield playfield;

        float playfieldPosX;
        float playfieldPosY;




        /*  Sets window as nullptr before getting initialized. More a style thing.
            @return void
        */  
        void initVariables();

        /*  Initializes the window.
            @return void
        */
        void initWindow();

        void initPlayfield();

        void initPlayer();

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

        /*  It's the getter for the Videomode.
            @return sf::VideoMode
        */
        sf::VideoMode getVMode();

        /*  Like a event manager. It's active while running == true and checks every frame, if one of these Events happend.
            If so do action.
            @return void
        */
        void pollEvents();

        void updateInput();

        /*  Executes the pollEvents function. Basically it the "update" of the game, by checking at the beginnig of the
            frame, if a Event happend and if so, handle it.
            @return void
        */
        void update();

        void updateCollisonWindow();

        void updateCollisonPlayfiled();

        /*  Displays the window after all events got handled. display() needs to be the last function in render(), because you 
            have to make sure that all Elements of your Game are set in your window before displaying it.
            @return void
        */
        void render();
};
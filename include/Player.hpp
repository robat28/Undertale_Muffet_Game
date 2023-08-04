#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player {
    private:

        sf::RectangleShape shape;

        float movementSpeed;

        /*  
            @return void
        */  
        void initVariables();

        /*  Initializes the Player model.
            @return void
        */
        void initPlayer();

    public:

        /*  Constructor

        */
        Player(float x = 10.f, float y = 10.f);

        /*  Destructor
            Destroys the Object after usage. 
        */
        ~Player();

        void updateInput();

        void update(sf::RenderTarget* target);

        void render(sf::RenderTarget* target);

};
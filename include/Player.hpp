#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Player {
    private:

        sf::Sprite sprite;
        sf::Texture texture;

        float movementSpeed;

        void initTexture();
        void initSprite();

    public:

        /*  Constructor

        */
        Player();

        /*  Destructor
            Destroys the Object after usage. 
        */
        ~Player();

        void move(const float x, const float y);

        void update(const sf::RenderTarget* target);

        void render(sf::RenderTarget& target);

};
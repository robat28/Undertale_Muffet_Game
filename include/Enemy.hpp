#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Enemy{
    private:

        // Enemy Variables
        float movementspeed;

        // Texture of Enemies
        sf::Texture texture;
        sf::Sprite sprite;

        // Private Functions
        void initVariables();
        void initSprite();
        void loadEnemyTexture();


    public:

        // Constructor
        Enemy();

        // Destructor
        ~Enemy();

        // Public Functions
        void render(sf::RenderTarget& target);
};
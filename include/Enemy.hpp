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
        int spawnPosition;

        // Texture of Enemies
        sf::Texture texture;
        sf::Sprite sprite;

        // Private Functions
        void initVariables();
        void initSprite();
        void loadEnemyTexture();


    public:

        // Constructor
        Enemy(float x, float y, const int spawnPosition);

        // Destructor
        ~Enemy();

        // Getter
        const sf::FloatRect getBounds() const;

        // Setter
        void setPosition(const float x, const float y);

        // Public Functions
        void update();
        void render(sf::RenderTarget& target);
};
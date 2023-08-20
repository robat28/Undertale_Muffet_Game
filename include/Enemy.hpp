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
        float movementSpeed;
        int spawnPosition;
        float spriteSize;

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
        Enemy(float x, float y, const int spawnPosition);

        // Destructor
        ~Enemy();

        // Getter
        const sf::FloatRect getBounds() const;
        const float getSize() const;
        const int getSpawnPoint() const;

        // Setter
        void setPosition(const float x, const float y);

        // Public Functions
        void move(const float& x, const float& y);
        void update();
        void render(sf::RenderTarget& target);
};
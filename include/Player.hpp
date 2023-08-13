#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

enum LEVEL{
    TOP, 
    MIDDLE,
    BOTTOM
};

class Player {
    private:

        // Player Variables
        float movementSpeed;
        LEVEL currentLevel;

        // Texture of Player
        sf::Sprite sprite;
        sf::Texture texture;

        // Private Functions
        void initPlayer();
        void initTexture();
        void initSprite();

    public:

        // Constructor
        Player();

        // Destructor
        ~Player();

        // Getter
        const sf::FloatRect getBounds() const;
        const float getHeight() const;
        const float getWidth() const;
        const LEVEL getCurrentLevel();

        // Setter
        void setNewLevel(LEVEL newLevel);
        void setPosition(const float& x, const float& y);

        // Public Functions
        void move(const float& x, const float& y);
        void render(sf::RenderTarget& target);
};
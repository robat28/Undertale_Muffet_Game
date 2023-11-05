#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

enum LEVEL{
    TOP, 
    MIDDLE,
    BOTTOM
};

class Player {
    private:
        std::string dataDir;

        // Player Variables
        float hp;
        float hpMax;
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
        Player(std::string dataDir);

        // Destructor
        ~Player();

        // Getter
        const sf::FloatRect getBounds() const;
        const float getHeight() const;
        const float getWidth() const;
        const LEVEL getCurrentLevel();
        const float getHp();
        const float getHpMax();

        // Setter
        void setNewLevel(LEVEL newLevel);
        void setPosition(const float& x, const float& y);
        void setColor(const float r, const float g, const float b, const float transp);

        // Public Functions
        void move(const float& x, const float& y);
        void takeDamage(const float& damage);
        void render(sf::RenderTarget& target);

};

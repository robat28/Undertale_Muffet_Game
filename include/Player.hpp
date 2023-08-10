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

        sf::Sprite sprite;
        sf::Texture texture;

        float movementSpeed;
        LEVEL currentLevel;

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

        const sf::FloatRect getBounds() const;

        const float getHeight() const;
        const float getWidth() const;
        
        LEVEL getCurrentLevel();
        void setNewLevel(LEVEL newLevel);

        void setPosition(const float x, const float y);

        void move(const float x, const float y);

        void update(const sf::RenderTarget* target);
        void render(sf::RenderTarget& target);

};
#ifndef _PLAYER_
#define _PLAYER_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>


enum LEVEL{TOP, MIDDLE, BOTTOM};

class Player {
    private:
    
        std::string dataDir;

        // Player Variables
        float hp;
        float hpMax;
        float movementSpeed;
        LEVEL currentLevel;

        // Texture of Player
        sf::Texture defeatTexture;
        sf::Texture texture;
        std::unique_ptr<sf::Sprite> sprite;
        std::unique_ptr<sf::Sprite> defeatSprite;
        
        // Private Functions
        void initVariables();
        void initSprites();
        void loadTexture();

    public:

        // Constructor
        Player(std::string dataDir);

        // Getter
        const float getHeight() const;
        const float getWidth() const;
        const sf::FloatRect getBounds() const;
        const LEVEL getCurrentLevel();
        const float getHp();
        const float getHpMax();

        // Setter
        void setNewLevel(LEVEL newLevel);
        void setPosition(const float& x, const float& y);
        void setColor(const float r, const float g, const float b, const float transp);
        void setTexture();
        void setDefeatTexture();

        // Public Functions
        void move(const float& x, const float& y);
        void takeDamage(const float& damage);
        void render(sf::RenderTarget& target);
};

#endif
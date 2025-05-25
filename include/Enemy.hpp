#ifndef _ENEMY_
#define _ENEMY_

#include <SFML/Graphics.hpp>
#include <iostream>


class Enemy{
    private:

        std::string dataDir;

        // Enemy Variables
        int spawnPosition;
        float movementSpeed;
        float spriteSize;

        // Texture of Enemies
        sf::Texture texture;
        std::unique_ptr<sf::Sprite> sprite;

        // Private Functions
        void initVariables();
        void initSprite();
        void loadTexture();

    public:

        // Constructor
        Enemy();
        Enemy(float x, float y, const int spawnPosition, std::string dataDir);

        // Getter
        const sf::FloatRect getBounds() const;
        const float getSize() const;
        const int getSpawnPoint() const;

        // Setter
        void setPosition(const float x, const float y);

        // Public Functions
        void move(const float& x, const float& y);
        void render(sf::RenderTarget& target);
};

#endif 

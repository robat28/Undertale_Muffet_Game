#pragma once

#include "Player.hpp"

class GUI {
    private:
        std::string dataDir;

        // Animation Variables
        int numFrames;
        int frameLength;
        sf::Time frameDuration;
        sf::IntRect frameRect;
        int currentFrame;

        // Texture of Animation
        sf::Texture spritesheetTexture;
        std::unique_ptr<sf::Sprite> sprite;

        // Timer
        sf::Time totalTime;

        // HP-Bar
        sf::Font font;
        std::unique_ptr<sf::Text> healthText;
        std::unique_ptr<sf::Text> playerName;
        sf::RectangleShape healthBarRemaining;
        sf::RectangleShape healthBarLost;

        // Sounds
        sf::SoundBuffer hitBuffer; 
        sf::SoundBuffer defeatBuffer;
        sf::SoundBuffer gameOverBuffer;
        std::unique_ptr<sf::Sound> hitSound;
        std::unique_ptr<sf::Sound> defeatSound;
        std::unique_ptr<sf::Sound> gameOverTheme;

        sf::Music ingameOST;
        
        // Private Functions
        void initAnimationVariables();

        void initSprite();
        void loadSpriteSheetTexture();

        void initSounds();
        void loadSounds();
        void loadMusic();

        void loadFont();
        void initHUD();
        void initHealthText();
        void initPlayerName();
        void initHealthBar();



    public:

        // Constructor
        GUI(std::string dataDir);

        // Destructor
        ~GUI();

        // Getter
        const float getSpriteWidth() const;
        const float getSpriteHeight() const;
        sf::Sound getHitSound();

        // Setter
        void setSpritePosition(const float& x, const float& y);
        void setNewSpritePosition(const float& x, const float& y);
        void setFrameRect(const int& currentFrame);
        void setHPBarPosition(const float& x, const float& y);
        void setSize(sf::Vector2f size);
        void setHpString(const int& currentHp);

        // Public Functions
        void playHitSound();
        void playMusic();
        void playDefeatSound();
        void playGameOverSound();
        void stopGameOverSound();
        void stopMusic();

        void showGameOver();


        void updateSprite(sf::Time& deltaTime);
        void render(sf::RenderTarget& target);
};

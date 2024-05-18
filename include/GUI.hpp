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
        sf::Sprite sprite;

        // Timer
        sf::Time totalTime;

        // HP-Bar
        sf::Font font;
        sf::Text healthText;
        sf::Text playerName;
        sf::RectangleShape healthBarRemaining;
        sf::RectangleShape healthBarLost;

        // Sounds
        sf::SoundBuffer hitBuffer;
        sf::SoundBuffer defeatSoundBuffer;
        sf::SoundBuffer gameOverThemeBuffer;

        sf::Sound hitSound;
        sf::Sound defeatSound;
        sf::Sound gameOverTheme;

        sf::Music ingameOST;


        // Game Over Screen
        sf::Text gameOverTextTop;
        sf::Text gameOverTextBottom;
        sf::Text gameOverMessage;
        
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
        void initGameOverText();

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
        void setGameOverVisibility(const int& visibility);
        void setGameOverTextPosition(const int& x, const int& y);

        // Public Functions
        void playHitSound();
        void playMusic();
        void playDefeatSound();
        void playGameOverSound();
        void stopMusic();

        void showGameOver();


        void updateSprite(sf::Time& deltaTime);
        void render(sf::RenderTarget& target);
        void renderGameOver(sf::RenderTarget& target);
};

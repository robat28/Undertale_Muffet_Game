#pragma once

#include "GUI.hpp"

class Playfield {
    private:

        sf::RectangleShape playfield;

        void initPlayfield();

        void initLevels();

    public:

        std::vector<sf::RectangleShape> levels;

        Playfield();

        ~Playfield();

        const sf::FloatRect getBounds() const;

        const float getHeight() const;

        const float getWidth() const;


        void setPosition(const float x, const float y);

        void setLevelPositions(const float x, const float y);

        void setColor();


        void update();

        void render(sf::RenderTarget* target);
};
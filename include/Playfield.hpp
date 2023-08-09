#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Playfield {
    private:

        sf::RectangleShape playfield;

        float xCenter;
        float yCenter;

        void initVariables();

    public:

        Playfield();
        ~Playfield();

        const sf::FloatRect getBounds() const;
        void setPosition(const float x, const float y);

        void update();
        void render(sf::RenderTarget* target);
};
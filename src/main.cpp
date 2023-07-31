#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


int main() {

    sf::RenderWindow window(sf::VideoMode(1200, 800), "robat game", sf::Style::Titlebar | sf::Style::Close);
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Red);
    sf::Event evnt;

    while (window.isOpen()) {

        switch(window.pollEvent(evnt)) {

            case sf::Event::Closed: 
                window.close();
                break; 
            case sf::Event::KeyPressed:
                if(evnt.key.code == sf::Keyboard::Escape)
                    window.close();
                break;    

        }

        // Clears old frame
        window.clear();


        window.draw(shape);

        // Tell app that window is done drawing
        window.display();
        
    }

    return 0;
}
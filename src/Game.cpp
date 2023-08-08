#include "Game.hpp"

/* 
    private Functions
*/ 

/*  Sets window as nullptr before getting initialized. More a style thing.
    @return void
*/  
void Game::initVariables() {
    this->window = nullptr;
}

/*  Initializes the window.
    @return void
*/
void Game::initWindow() {
    this->vMode.height = 600;
    this->vMode.width = 800;

    this->window = new sf::RenderWindow(this->vMode, "robat game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
} 

/*
    public Functions
*/

/*  Constructor
    After creating a Game instance, all variables and the window are getting intitialized. 
*/
Game::Game() {
    this->player = new Player();

    this->initVariables();
    this->initWindow();
}

/*  Destructor
    Destroys the Object after usage. 
*/
Game::~Game() {
    delete this->window;
    delete this->player;
}

/*  Returns true, if the window is still open and returns false, if the window got closed.
    @return bool
*/
const bool Game::running() const {
    return this->window->isOpen();
}

/*  Like a event manager. It's active while running == true and checks every frame, if one of these Events happend.
    If so do action.
    @return void
*/
void Game::pollEvents() {

    while(this->window->pollEvent(this->evnt)) {

        switch(this->evnt.type) {
            case sf::Event::Closed: 
                this->window->close();
                break; 
            case sf::Event::KeyPressed:
                if(evnt.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;    
        }
    }
}

void Game::updateInput() {
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->player->move(-1.f, 0.f);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->player->move(1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->player->move(0.f, -1.f);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->player->move(0.f, 1.f);
    }

    // Player Window Collison
    this->updateCollison();

}

void Game::updateCollison() {
    //Left
    if(this->player->getBounds().left < 0.f) {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }
    //Right
    else if(this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x) {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }
    //Top
    if(this->player->getBounds().top < 0.f) {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }
    //Bottom
    else if(this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y) {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }


}

/*  Executes the pollEvents function. Basically it the "update" of the game, by checking at the beginnig of the
    frame, if a Event happend and if so, handle it.
    @return void
*/
void Game::update() {

    this->pollEvents();
    this->updateInput();
}

/*  Displays the window after all events got handled. display() needs to be the last function in render(), because you 
    have to make sure that all Elements of your Game are set in your window before displaying it.
    @return void
*/
void Game::render() {
    this->window->clear();

    // Render stuff
    this->player->render(*this->window);

    this->window->display();
}

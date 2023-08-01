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
} 

/*
    public Functions
*/

/*  Constructor
    After creating a Game instance, all variables and the window are getting intitialized. 
*/
Game::Game() {
    this->initVariables();
    this->initWindow();
}
/*  Destructor
    Destroys the Object after usage. 
*/
Game::~Game() {
    delete this->window;
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

/*  Executes the pollEvents function. Basically it the "update" of the game, by checking at the beginnig of the
    frame, if a Event happend and if so, handle it.
    @return void
*/
void Game::update() {
    this->pollEvents();
}

/*  Displays the window after all events got handled. display() needs to be the last function in render(), because you 
    have to make sure that all Elements of your Game are set in your window before displaying it.
    @return void
*/
void Game::render() {
    this->window->clear(sf::Color::Blue);

    this->window->display();
}

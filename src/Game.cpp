#include "Game.hpp"

/* 
    private Functions
*/ 

/*  Sets window as nullptr before getting initialized. More a style thing.
    @return void
*/  
void Game::initVariables() {
    this->window = nullptr;
    this->playfieldPosX = 0.f;
    this->playfieldPosY = 0.f;

}

/*  Initializes the window.
    @return void
*/
void Game::initWindow() {
    this->vMode.width = 800;
    this->vMode.height = 600;
    this->window = new sf::RenderWindow(this->vMode, "robat game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);

    this->playfieldCenterX = this->window->getSize().x / 2.f;
    this->playfieldCenterY = this->window->getSize().y / 1.5f;
} 

void Game::initPlayfield() {
    this->playfieldPosX = playfieldCenterX - (this->playfield.getWidth() / 2.f - 5.f);
    this->playfieldPosY = playfieldCenterY - (this->playfield.getHeight() / 2.f - 5.f);
    this->playfield.setPosition(playfieldPosX, playfieldPosY);
}

void Game::initPlayer() {
    this->player->setPosition(this->window->getSize().x / 2.f - this->player->getWidth() / 2.f, 
                              this->playfield.getBounds().top + this->playfield.getHeight() / 2 - this->player->getHeight() / 2.f);
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
    this->initPlayfield();
    this->initPlayer();
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
            default:
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
    this->updateCollisonPlayfiled();

}

void Game::updateCollisonWindow() {
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

void Game::updateCollisonPlayfiled() {
    //Left
    if(this->player->getBounds().left < this->playfield.getBounds().left + 5) {
        this->player->setPosition(this->playfield.getBounds().left + 5, this->player->getBounds().top);
    }
    //Right
    else if(this->player->getBounds().left + this->player->getBounds().width > this->playfield.getBounds().left + this->playfield.getBounds().width - 5) {
        this->player->setPosition(this->playfield.getBounds().left + this->playfield.getBounds().width - this->player->getBounds().width - 5, this->player->getBounds().top );
    }
    //Top
    if(this->player->getBounds().top < this->playfield.getBounds().top + 5) {
        this->player->setPosition(this->player->getBounds().left, this->playfield.getBounds().top + 5);
    }
    //Bottom
    else if(this->player->getBounds().top + this->player->getBounds().height > this->playfield.getBounds().top + this->playfield.getBounds().height - 5) {
        this->player->setPosition(this->player->getBounds().left, this->playfield.getBounds().top + this->playfield.getBounds().height - this->player->getBounds().height - 5);
    }
}




/*  Executes the pollEvents function. Basically it the "update" of the game, by checking at the beginnig of the
    frame, if a Event happend and if so, handle it.
    @return void
*/
void Game::update() {

    this->pollEvents();
    this->updateInput();
    //std::cout << this->player->getBounds().getPosition().y << '\n';
}

/*  Displays the window after all events got handled. display() needs to be the last function in render(), because you 
    have to make sure that all Elements of your Game are set in your window before displaying it.
    @return void
*/
void Game::render() {
    this->window->clear();

    // Render stuff
    this->playfield.render(this->window);
    this->player->render(*this->window);


    this->window->display();
}

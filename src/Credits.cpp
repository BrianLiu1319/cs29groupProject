#include "Credits.hpp"

/*********************************
 Draws the Credits screen.
 *********************************/
void Credits::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(backButton);
}

/*********************************
Constructor.
 Sets up everything according
 to the window size.
*********************************/
Credits::Credits(sf::Vector2f windowSize) : Menu(windowSize) {
    
    //Calculate Button sizes and positions
    sf::Vector2f buttonSize(windowSize.y / 1080.0f * 135.0f, windowSize.y / 1080.0f * 135.0f);
    
    //Set Buttons
    backButton.setSize(sf::Vector2f(buttonSize.y, buttonSize.y));
    backButton.setPosition(windowSize.x / 1920.0f * 20.0f, windowSize.x / 1920.0f * 20.0f);
    backButton.setOutlineThickness(buttonSize.y / 20.0f);
    
    //Set Textures
    try {
        setBgTexture(menuBackgroundTexturePath);
        setBackTexture(backButtonPath, backButtonInvPath);
        setClickSound(clickSFXPath01);
    } catch (const std::string& fileName) {
        std::cerr << "Unable to open the file " << fileName << std::endl;
        std::cerr << "Location: Credits" << std::endl;
        exit(1);
    }
}

/*********************************
Sets the texture and inverse
 texture of the back button.
*********************************/
void Credits::setBackTexture(std::string path, std::string pathInv) {
    if(!backTexture.loadFromFile(path)) {
        throw(std::string(path));
    }
    if(!backTextureInv.loadFromFile(pathInv)) {
        throw(std::string(pathInv));
    }
    
    backButton.setTexture(&backTexture);
}

/*********************************
Runs the credits screen.
*********************************/
int Credits::run(sf::Vector2f mousePos) {
    
    /***
     states:
     0 - Credits
     1 - Back to Settings Menu
     */
    int state = 0;
    
    /*********************************
    Handle actions on the back button.
    *********************************/
    if(isMouseOver(mousePos, backButton)) {
        
        /*********************************
        When mouse is hovering over
         the button:
        *********************************/
        backButton.setOutlineColor(sf::Color::White);
        backButton.setTexture(&backTextureInv);
        
        /*********************************
        When mouse clicks the button:
        *********************************/
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseStartClick) {
            if(!muteSfx) click.play();
            mouseStartClick = false;
        } else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseStartClick) {
            state = 1;
            backButton.setTexture(&backTexture);
            backButton.setOutlineColor(sf::Color::Transparent);
            mouseStartClick = true;
        }
        
        /*********************************
        When mouse leaves the button:
        *********************************/
    } else if (backButton.getOutlineColor() != sf::Color::Transparent){
        backButton.setOutlineColor(sf::Color::Transparent);
    } else if (backButton.getTexture() != &backTexture) {
        backButton.setTexture(&backTexture);
    }
    
    return state;
}

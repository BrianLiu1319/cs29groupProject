#include "Attacker.hpp"

Attacker::Attacker() :
    Collider(catSpritePath, LEFT, { WINDOW_WIDTH - 20,360 }, 100, 10.0f),
    animator(catSpritePath, sf::Vector2u(4, 2), 1.0f / 3.0f)
{
    updateAnimation(0.0f);
    scale(0.5, 0.5);
    Vector2f origin(0, getGlobalBounds().height / 2.0f);
    setOrigin(origin);
    
    //ADDNEW3 sfx
    setSfx();
};

Attacker::Attacker(sf::Vector2f a) :
    Collider(catSpritePath, LEFT, { WINDOW_WIDTH, a.y + 47.0f }, 100, 10.0f),
    animator(catSpritePath, sf::Vector2u(4, 2), 1.0f / 3.0f)
{
    updateAnimation(0.0f);
    scale(0.5, 0.5);
    Vector2f origin(0, getGlobalBounds().height);
    setOrigin(origin);
    
    //ADDNEW3
    setSfx();
}

Attacker::Attacker(sf::Vector2f a, string b) : 
    Collider(b, LEFT, { WINDOW_WIDTH, a.y + 47.0f }, 100, 10.0f),
    animator(b, sf::Vector2u(4, 2), 1.0f / 3.0f)
{
    updateAnimation(0.0f);
    scale(0.5, 0.5);
    Vector2f origin(0, getGlobalBounds().height);
    setOrigin(origin);
    if (b == (assetFolder + "catSprites2.png"))
    {
        health = 200;
    }
    else if (b == (assetFolder + "catSprites3.png"))
    {
        health = 150;
    }
    
    //ADDNEW3
    setSfx();
   
};

void Attacker::updateObject() {
    //does not move anymore if defeated
    if(currState != defeated) {
        if (defaultDirection == LEFT) autoTravel(LEFT);
        else if (defaultDirection == RIGHT) autoTravel(RIGHT);
    }
}

/**************
Updates the current frame
 of the animation.
**************/
void Attacker::updateAnimation(float deltaTime) {
    animator.update(deltaTime);
    setTextureRect(animator.uvRect);
}

/**************
 Returns true if the Attacker
 has been defeated
 AND the defeat animation
 has stopped playing.
 Returns false otherwise.
 **************/
bool Attacker::isDefeated() const {
    if(currState == defeated && animator.isLastFrame()) {
        return true;
    }
    return false;
}

/**************
Sets the Attacker to be defeated.
 Switches the animation to
 the defeat animation and prevents
 it from looping.
**************/
void Attacker::setDefeated() {
    currState = defeated;
    animator.setLoop(false);
    animator.setActiveRow(1);
}

/**************
Sets the Attacker to be moving.
 Switches the animation to
 the moving animation and makes
 it loop.
**************/
void Attacker::setMoving() {
    currState = moving;
    animator.setLoop(true);
    animator.setActiveRow(0);
}


void Attacker::meow() {
    //it's too noisy T-T so it just plays half of the time
    int random = rand() % 2;
    if(!random) meowSfx.play();
}

void Attacker::sadSound() {
    defeatSfx.play();
}

void Attacker::setSfx() {
    //ADDNEW3 for sfx
    try {
        if(!meowSfxBuffer.loadFromFile(meowFile)) {
            throw meowFile;
        }
        if(!defeatSfxBuffer.loadFromFile(defeatFile)) {
            throw defeatFile;
        }
        meowSfx.setBuffer(meowSfxBuffer);
        meowSfx.setVolume(10.0f);
        defeatSfx.setBuffer(defeatSfxBuffer);
        defeatSfx.setVolume(20.0f);
    } catch (const std::string& fileName) {
        std::cerr << "Unable to open the file " << fileName << std::endl;
        std::cerr << "Location: HowToPlay" << std::endl;
        exit(1);
    }
}

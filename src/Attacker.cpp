#include "Attacker.hpp"

Attacker::Attacker() :
    Collider(catSpritePath, LEFT, { WINDOW_WIDTH - 20,360 }, 100, 10.0f),
    animator(catSpritePath, sf::Vector2u(4, 2), 1.0f / 3.0f)
{
    updateAnimation(0.0f);
    scale(0.5, 0.5);
    Vector2f origin(0, getGlobalBounds().height / 2.0f);
    setOrigin(origin);
    
};

Attacker::Attacker(sf::Vector2f a) :
    Collider(catSpritePath, LEFT, { WINDOW_WIDTH, a.y + 47.0f }, 100, 10.0f),
    animator(catSpritePath, sf::Vector2u(4, 2), 1.0f / 3.0f)
{
    updateAnimation(0.0f);
    scale(0.5, 0.5);
    Vector2f origin(0, getGlobalBounds().height);
    setOrigin(origin);
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

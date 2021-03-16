#include "Defender.hpp"

Defender::Defender(sf::Vector2f a) :
    Collider(dogeTower, RIGHT, { a.x, a.y + 47.0f }, 100, 0.0f),
    animator(dogeTower, sf::Vector2u(4, 2), 1.0f / 3.0f)
{
    scale(0.5, 0.5);
    Vector2f origin(0, getGlobalBounds().height / 2.0f);
    setOrigin(origin);
};

void Defender::updateObject() {
    if (defaultDirection == LEFT) autoTravel(LEFT);
    else if (defaultDirection == RIGHT) autoTravel(RIGHT);
}

/**************
Updates the current frame
 of the animation.
**************/
void Defender::updateAnimation(float deltaTime) {
    animator.update(deltaTime);
    setTextureRect(animator.uvRect);
}

/**************
 Returns true if the Defender
 has been defeated
 AND the defeat animation
 has stopped playing.
 Returns false otherwise.
 **************/
bool Defender::isDefeated() const {
    if(currState == defeated && animator.isLastFrame()) {
        return true;
    }
    return false;
}

/**************
Sets the Defender to be defeated.
 Switches the animation to
 the defeat animation and prevents
 it from looping.
**************/
void Defender::setDefeated() { // in main add check for dying to prevent looping to setDefeeated?    
    currState = defeated;
    animator.setLoop(false);
    animator.setActiveRow(1);
}

/**************
Sets the Defender to be standing.
 Switches the animation to
 the standing animation and makes
 it loop.
**************/
void Defender::setStanding() {
    currState = standing;
    animator.setLoop(true);
    animator.setActiveRow(0);
}

//
//  Defender.hpp
//  SFML testing
//
//  Created by Jessica Susilo on 13/03/21.
//  Copyright © 2021 Jessica Susilo. All rights reserved.
//

#ifndef Defender_hpp
#define Defender_hpp

#include "Collider.h"

class Defender : public Collider {
private:
    int price{ 40 };
    Animation animator;
    
    enum STATES { standing, defeated };
    STATES currState = standing;
    void fire() {
        // create a bullet object
    }
public:

    Defender(sf::Vector2f a);
    void updateAnimation(float deltaTime);
    void updateObject();
 
    bool isDefeated() const;
    void setDefeated();
    void setStanding();

};

#endif /* Defender_hpp */

//
//  Defender.hpp
//  SFML testing
//
//  Created by Jessica Susilo on 13/03/21.
//  Copyright © 2021 Jessica Susilo. All rights reserved.
//

#ifndef Defender_hpp
#define Defender_hpp

#include "Collider.hpp"

class Defender : public Collider {
private:
    
    //ADDNEW3 for sfx!
    const std::string barkFile = assetFolder + "dog bark.wav";
    const std::string defeatFile = assetFolder + "dog defeat.wav";
    sf::SoundBuffer barkSfxBuffer, defeatSfxBuffer;
    sf::Sound barkSfx, defeatSfx;
    
    int price{ 40 };
    Animation animator;
    
    enum STATES { standing, defeated };
    STATES currState = standing;
    void fire() {
        // create a bullet object
    }
    
    //ADDNEW to store land index
    int landIndex;
    
    
public:
    Defender() = default;
    Defender(sf::Vector2f a);
    void updateAnimation(float deltaTime);
    void updateObject();
 
    bool isDefeated() const;
    void setDefeated();
    void setStanding();
    
    //ADDNEW for checking landindex
    void setLandIndex(int i) { landIndex = i; }
    int getLandIndex() const { return landIndex; }
    
    //ADDNEW
    void increaseHealth(unsigned h) { health += h; }
    
    //ADDNEW3
    void bark();
    void sadSound();

};

#endif /* Defender_hpp */

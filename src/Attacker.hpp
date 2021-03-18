#ifndef Attacker_hpp
#define Attacker_hpp

#include "Collider.hpp"

class Attacker : public Collider {
    void attack() { }
    Animation animator;
    
    enum STATES { moving, defeated };
    STATES currState = moving;
    
    //ADDNEW3 for sfx!
    const std::string meowFile = assetFolder + "cat meow.wav";
    const std::string defeatFile = assetFolder + "cat defeat.wav";
    sf::SoundBuffer meowSfxBuffer, defeatSfxBuffer; 
    sf::Sound meowSfx, defeatSfx;
    void setSfx();
    
    
public:
    //    void hurt(Collider &other) override;
    Attacker();
    Attacker(sf::Vector2f a);
    Attacker(sf::Vector2f a, string b);
    void updateAnimation(float deltaTime);
    void updateObject();
    bool isDefeated() const;
    void setDefeated();
    void setMoving();
    
    //ADDNEW2
    bool isOnDefeat() const { if(currState == defeated) return true; else return false;}
    
    //ADDNEW3
    void meow();
    void sadSound();
};

#endif /* Attacker_hpp */

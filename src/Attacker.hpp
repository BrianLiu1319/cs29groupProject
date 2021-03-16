#ifndef Attacker_hpp
#define Attacker_hpp

#include "Collider.h"

class Attacker : public Collider {
    void attack() { }
    Animation animator;
    
    enum STATES { moving, defeated };
    STATES currState = moving;
public:
    //    void hurt(Collider &other) override;
    Attacker();
    Attacker(sf::Vector2f a);
    void updateAnimation(float deltaTime);
    void updateObject();
    bool isDefeated() const;
    void setDefeated();
    void setMoving();
};

#endif /* Attacker_hpp */

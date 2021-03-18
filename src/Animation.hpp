#ifndef Animation_hpp
#define Animation_hpp
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Animation {
    
private:
    unsigned numOfRows;
    unsigned activeRow;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;
    unsigned* numOfSpritesInRow;
    bool loop;
    
public:
    //Animation();
    Animation(const sf::Texture& texture, const sf::Vector2u& imageCount, float switchTime);
    Animation(const std::string& texturePath, const sf::Vector2u& imageCount, float switchTime);
    ~Animation();
    sf::IntRect uvRect;
    
    void update(unsigned row, float deltaTime);
    void update(float deltaTime);
    void setNumOfSpritesInRow(unsigned row, unsigned num);
    void setActiveRow(unsigned row);
    bool isLastFrame() const;
    void setLoop(bool set);
};

#endif /* Animation_hpp */

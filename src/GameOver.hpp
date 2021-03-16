#ifndef GameOver_hpp
#define GameOver_hpp

#include "Menu.hpp"

class GameOver : public Menu {
    
private:
    //NOTE: go to Menu.hpp to change the folder path
    const std::string confirmButtonPath = assetFolder + "confirm button.png";
    const std::string confirmButtonInvPath = assetFolder + "confirm button inverted.png";
    const std::string fontPath = assetFolder + "AnonymousPro-Regular.ttf";
    const std::string clickSFXPath01 = assetFolder + "click02.wav";
    
    unsigned int score;
    sf::RectangleShape confirmButton;
    sf::Texture confirmButtonTexture, confirmButtonTextureInv;
    sf::Font textFont;
    sf::Text text;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setText();
    
public:
    GameOver(sf::Vector2f windowSize);
    int run(sf::Vector2f mousePos);
    void setConfirmButtonTexture(std::string path, std::string pathInv);
    void setFont(std::string path);
    void setScore(unsigned int s);
};

#endif /* GameOver_hpp */

#ifndef GameOver_hpp
#define GameOver_hpp

#include "Menu.hpp"
#include "FolderPath.hpp"

class GameOver : public Menu {
    
private:
    //NOTE: go to FolderPath.hpp to change the folder path
    const std::string confirmButtonPath = assetFolder + "confirm button.png";
    const std::string confirmButtonInvPath = assetFolder + "confirm button inverted.png";
    const std::string fontPath = assetFolder + "AnonymousPro-Regular.ttf";
    const std::string clickSFXPath01 = assetFolder + "click02.wav";
    //ADDNEW
    const std::string clawPath = assetFolder + "claw mark.png";
    //ADDNEW
    const std::string gameOverSoundPath = assetFolder + "game over.wav";
    
    unsigned int score;
    
    //ADDNEW add the claw mark
    sf::RectangleShape confirmButton, clawMark;
    //sf::RectangleShape confirmButton;
    
    //ADDNEW add the claw mark texture
    sf::Texture confirmButtonTexture, confirmButtonTextureInv, clawMarkTexture;
    //sf::Texture confirmButtonTexture, confirmButtonTextureInv;
    
    sf::Font textFont;
    sf::Text text;
    
    //ADDNEW
    sf::SoundBuffer gameOverSoundBuffer;
    //ADDNEW
    sf::Sound gameOverSound;
    //ADDNEW
    bool sfxHasPlayed = false;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setText();
    
    //ADDNEW
    void setGameOverSound();
    
public:
    GameOver(sf::Vector2f windowSize);
    int run(sf::Vector2f mousePos);
    void setConfirmButtonTexture(std::string path, std::string pathInv);
    void setFont(std::string path);
    void setScore(unsigned int s);
};

#endif /* GameOver_hpp */

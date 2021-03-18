#ifndef Toolbar_hpp
#define Toolbar_hpp

#include "Menu.hpp"

class Toolbar : public Menu {
    
private:
    
    //NOTE: Go to Folder.h to change the Folder Path.
    
    const std::string whistlePath = assetFolder + "whistle.png";
    const std::string whistlePathInv = assetFolder + "whistle inv.png";
    const std::string healthPath = assetFolder + "health.png";
    const std::string healthPathInv = assetFolder + "health inv.png";
    const std::string clickSFXPath01 = assetFolder + "click02.wav";
    
    sf::Texture whistleTexture, whistleTextureInv, healthTexture, healthTextureInv;
    sf::RectangleShape whistleButton, healthButton;
    enum SELECTION { none, whistle, health };
    SELECTION currentSelection = none;
    int healthCost = 100;
    int whistleRefund = 20;
    bool mute = false;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setWhistleTexture();
    void setHealthTexture();
    bool handleButton(sf::RectangleShape& button, const sf::Texture& buttonTexture, const sf::Texture& buttonInvTexture, const sf::Vector2f& mousePos);
    
public:
    
    Toolbar(sf::Vector2f windowSize);
    int run(sf::Vector2f mousePos);
    bool whistleSelected();
    bool healthSelected();
    void deselectAll();
    int getHealthCost() const { return healthCost; }
    int getWhistleRefund() const { return whistleRefund; }
    
};

#endif /* Toolbar_hpp */

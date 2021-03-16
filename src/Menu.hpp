#ifndef Menu_hpp
#define Menu_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Menu : public sf::Drawable {
    
protected:
    
    //Folder Path
    //C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/
    const std::string assetFolder = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/";
    //const std::string assetFolder = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/";
    
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::SoundBuffer clickBuffer;
    sf::Sound click;
    bool mouseStartClick; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool isMouseOver(sf::Vector2f mousePos, const sf::RectangleShape& button);
    bool muteSfx = false;
    
    bool handleButton(sf::RectangleShape& button, const sf::Texture& buttonTexture, const sf::Texture& buttonInvTexture, const sf::Vector2f& mousePos);
    
public:
    Menu(sf::Vector2f windowSize);
    void setBgTexture(std::string path);
    void setClickSound(std::string path);
    void toggleMuteSfx();
    virtual int run();
};

#endif /* Menu_hpp */

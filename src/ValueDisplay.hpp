#ifndef ValueDisplay_hpp
#define ValueDisplay_hpp

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "FolderPath.hpp"

class ValueDisplay : public sf::Drawable {
private:
    const std::string fontFile = assetFolder + "AnonymousPro-Regular.ttf";
    const std::string scoreDisplayPath = assetFolder + "score display.png";
    const std::string moneyDisplayPath = assetFolder + "money display.png";
    const int timeBeforeStart = 10;
    
    sf::Texture scoreDisplayTexture, moneyDisplayTexture;
    sf::RectangleShape scoreDisplay, moneyDisplay;
    sf::Font font;
    enum MODE { wave, countdown };
    MODE currentMode;
    sf::Text scoreText, moneyText, currentWave, waveCountdown;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
public:
    ValueDisplay(sf::Vector2f windowSize);
    void updateScore(int s);
    void updateMoney(int m);
    void setCountdownMode();
    void setWaveMode();
    void updateCountdown(int c);
    void updateWave(int w);
};

#endif /* ValueDisplay_hpp */

#ifndef StartMenu_hpp
#define StartMenu_hpp

#include "MainMenu.hpp"
#include "SettingsMenu.hpp"
#include "Credits.hpp"
#include "HowToPlay.hpp"
#include "Score.hpp"

class StartMenu : public sf::Drawable {
    
private:
    
    //Folder Path
   // C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/
       const std::string assetFolder = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/";
   // const std::string assetFolder = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/";

    //File Name
    const std::string menuBGMusicPath = assetFolder + "Wii Music.wav";
    
    MainMenu mainMenu;
    SettingsMenu settings;
    Credits credits;
    HowToPlay howToPlay;
    //sf::SoundBuffer bgMusicBuffer;
    sf::Music bgMusic;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    enum states { mainM, settingM, howToPlayM, creditsM };
    states gameState;
    int status;
    bool muteMusic = false;
    
public:
    StartMenu(sf::Vector2f windowSize);
    int run(sf::Vector2f mousePos);
    void setBgSound(std::string path);
    void updateScores(const Score& s) { mainMenu.updateScores(s); }
    bool isHighScore(const Score& s) const { return mainMenu.isHighScore(s); };
};

#endif /* StartMenu_hpp */

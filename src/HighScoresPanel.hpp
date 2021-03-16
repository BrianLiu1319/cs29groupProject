#ifndef HighScoresPanel_hpp
#define HighScoresPanel_hpp

#include <SFML/Graphics.hpp>
#include "Score.hpp"
#include <set>
#include <fstream>
#include <sstream>
#include <iomanip>

class HighScoresPanel : public sf::Drawable {
private:
    
    //Folder Path

   // C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/

    const std::string folderPath = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/";

   // const std::string folderPath = "/Users/jessicasusilo/Documents/Jessica S./DE ANZA/6 - Winter 2021/CIS 29/Project Assets/";
    
    //File Names
    const std::string highScoreFilePath = folderPath + "highScores.bin";
    const std::string panelTexturePath = folderPath + "high scores.png";
    const std::string fontPath = folderPath + "AnonymousPro-Regular.ttf";
    
    static const int maxScores = 10;
    
    std::multiset<Score, std::greater<Score>> scores;
    sf::RectangleShape panel;
    sf::Texture panelTexture;
    sf::Font textFont;
    sf::Text scoresText;
    
    void readHighScoresFile();
    void writeHighScoresFile();
    void updateScoresText();
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
public:
    HighScoresPanel(sf::Vector2f windowSize);
    void update(const Score& s);
    void testing();
    void setPanelTexture(std::string path);
    void setFont(std::string path);
    bool isHighScore(const Score& s) const;
};

#endif /* HighScoresPanel_hpp */

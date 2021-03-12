#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>
#include<fstream>
#include<iostream>
#include<string>
#include<thread>
#include<vector>
#include "Land.h"
#include "Inventory.h"
#include "Collider.h"
#include "Menu.hpp"
using namespace std;
using namespace sf;

class Game : public Menu {
private:
    const string path = "C:/Users/tommy/source/repos/jxsusilo/cs29groupProjectTrue/LATEST/assets/doge.png";
    //assetFolder is in Screen.hpp
    const std::string clickSFXPath01 = assetFolder + "click02.wav";
    
    Font font1;
    Event event;
    const int widthOfLand = 74;
    const int heightOfLand = 94;
    int money = 200;
    unsigned int score = 0;
    
    bool gameOver = false;
    bool muteSfx = false;
    
    void addBullet(vector<Bullet*>& things);
    void addBullet(vector<Bullet*>& things, Bullet* a);
    void addAttacker(vector<Attacker*>& attackers);
    void addAttacker(vector<Attacker*>& attackers, sf::Vector2f a);
    void gameClock(RenderWindow& window, vector<Collider*>& things);
    void checkCollision(vector<Attacker*>& attackers, vector<Bullet*>& bullets, vector<Defender*>& defenders);
    vector<Land*> genrateLandList();
    vector<Inventory*> generateInvenList();
    vector<Defender*> generateTowerList(vector <Land*> landList);
    int howManyTower(int money);
    Defender* defenderBuild(Land* aLand);
    void fire(Clock* clock, Defender* fireTower, vector<Bullet*> bulletList);
    void drawBuiltDefender(vector <Defender*> builtTowerList, RenderWindow& renderWindow);
    void showMoney(int money, RenderWindow& renderWindow);
    
public:
    Game(sf::Vector2f windowSize);
    int run(RenderWindow& renderWindow);
    unsigned int getScore() const { return score; }
    void toggleMuteSfx();
};

#endif /* Game_hpp */

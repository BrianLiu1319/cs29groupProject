#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>
//#include"SFML\Graphics.hpp"
#include<fstream>
#include<iostream>
#include<string>
#include<thread>
//#include<windows.h>
#include<vector>
#include "Land.h"
#include "Inventory.h"
#include "Collider.h"
#include "Menu.hpp"
#include "Attacker.hpp"
#include "Defender.hpp"
#include"Coin.h"
using namespace std;
using namespace sf;



class Game : public Menu {
private:
    const string path = assetFolder + "dogSprites.png";
    //assetFolder is in Menu.hpp
    const std::string clickSFXPath01 = assetFolder + "click02.wav";
    
    Font font1;
    Event event;
    const int widthOfLand = 74;
    const int heightOfLand = 94;
    int money = 200;
    unsigned int score = 0;
    sf::Clock animationClock;
    float animationDeltaTime = 0.0f;
    bool gaming = false;

    //*****************************
    // Steven's Added stuff
    //*****************************

    //this thread generate cats
    Thread* a_TGenerate = nullptr;// this thread for automaticlly control cat waves;
    thread* moveThread;
    bool waving = true;

    Mutex threadLock;
    int waveGrade = 0;

    bool bThread = true;			// We probably won't use the thread stuff? but it's here for now. 
    bool bExitThread = false;
    
    bool gameOver = false;
    bool muteSfx = false;

    
    struct MyStruct
    {
        vector <Land*>* lands;		// important: lands should be a pointer
        vector<Attacker*>* attackers;
    };
    
    /*
     Difficulty Levels:
     1 - Easy
     2 - Medium
     3 - Hard
     Default level is Easy.
     */
    int difficulty = 1;
    
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

    //**********************
    // Added this 3/15
    //**********************

    coinMaker* buildCoinMaker(Land* land);
    void coinCollectin(vector<coinMaker*>& makerList);
    void enmyReminder(string txt, RenderWindow& renderWindow);
    void randomGenerCats(const vector <Land*>& landList,vector <Attacker*>& allAttackers);
    int wave(string special);

    //void regularGenerAttacter(vector <Land*>* aLandList, vector <Attacker*>& allAttackers);
    void regularGenerAttacter(MyStruct* ms);
    //void generateAttacter(vector <Land*>* aLandList, vector <Attacker*>& allAttackers);
    void generateAttacter(MyStruct* ms);

    //**********************************
    // End of added functions 3/15
    //**********************************


    void fire(Clock* clock, Defender* fireTower, vector<Bullet*> bulletList);
    void drawBuiltDefender(vector <Defender*> builtTowerList, RenderWindow& renderWindow);
    void showMoney(int money, RenderWindow& renderWindow);
    
    void updateAnimations(vector<Defender*>& defenders, vector<Attacker*>& attackers);
    
public:
    Game(sf::Vector2f windowSize);
    int run(RenderWindow& renderWindow);
    unsigned int getScore() const { return score; }
    void toggleMuteSfx();
    void increaseDifficulty() { difficulty++; }
    void decreaseDifficulty() { difficulty--; }
};

#endif /* Game_hpp */

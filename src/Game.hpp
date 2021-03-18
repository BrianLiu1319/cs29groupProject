#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>
#include<fstream>
#include<iostream>
#include<string>
#include<thread>
#include<vector>
#include "Land.hpp"
#include "Inventory.hpp"
#include "Collider.hpp"
#include "Menu.hpp"
#include "Attacker.hpp"
#include "Defender.hpp"
#include "Coin.hpp"
//ADDNEW there was an extra semicolon after FolderPath.h
#include "FolderPath.hpp"
//ADDNEW include toolbar
#include "Toolbar.hpp"
//ADDNEW2 include ValueDisplay (to display money and score)
#include "ValueDisplay.hpp"


using namespace std;
using namespace sf;


class Game : public Menu {
private:
    //assetFolder is in FolderPath.hpp
    const string path = assetFolder + "dogSprites.png";
    const std::string clickSFXPath01 = assetFolder + "click02.wav";
    //ADDNEW
    const std::string bgMusicPath = assetFolder + "background music.wav";
    //ADDNEW
    const std::string bgTexturePath = assetFolder + "game background-01.png";
    
    Font font1;
    Event event;
    const int widthOfLand = 74;
    const int heightOfLand = 94;
    int money = 200;
    unsigned int score = 0;
    sf::Clock animationClock;
    float animationDeltaTime = 0.0f;
    bool gaming = false;
    
    //ADDNEW
    Toolbar tools;
    sf::Music bgMusic;
    bool muteMusic = false;
    //ADDNEW2
    ValueDisplay statsDisplay;
    bool onWave = false;
    

    //*****************************
    // Steven's Added stuff
    //*****************************

    //this thread generate cats
    //ADDNEW commented this out for now
    /*
    Thread* a_TGenerate = nullptr;// this thread for automaticlly control cat waves;
    thread* moveThread;
    bool waving = true;

    
    int waveGrade = 0;

    bool bThread = true;			// We probably won't use the thread stuff? but it's here for now. 
    bool bExitThread = false;
     
     struct MyStruct
     {
         vector <Land*>* lands;        // important: lands should be a pointer
         vector<Attacker*>* attackers;
     };
    */
    Mutex threadLock;
    

    
    
    bool gameOver = false;
    //ADDNEW3 get rid of mutesfx here
    //bool muteSfx = false;
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
    void checkCollision(vector<Attacker*>& attackers, vector<Bullet*>& bullets, vector<Defender*>& defenders, vector<coinMaker*>& makers);
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
    
    //ADDNEW commented this out for now
    /*
    void enmyReminder(string txt, RenderWindow& renderWindow);
    void randomGenerCats(const vector <Land*>& landList,vector <Attacker*>& allAttackers);
    int wave(string special);
    //void regularGenerAttacter(vector <Land*>* aLandList, vector <Attacker*>& allAttackers);
    void regularGenerAttacter(MyStruct* ms);
    //void generateAttacter(vector <Land*>* aLandList, vector <Attacker*>& allAttackers);
    void generateAttacter(MyStruct* ms);
     */

    //for testing
    void simpleAttackerGenerator(vector<Attacker*>& attackers, const vector<Land*>& landList);
    sf::Clock generatorClock;
    float deltaGenTime = 0.0f;
    float waveGenTime = 0.0f;
    bool waveStart = false;
    int numDogsInBigWave = 0;
    
    //ADDNEW2 change this to 1
    int currentWave = 1;
    
    
    
    //**********************************
    // End of added functions 3/15
    //**********************************


    void fire(Clock* clock, Defender* fireTower, vector<Bullet*> bulletList);
    void drawBuiltDefender(vector <Defender*> builtTowerList, RenderWindow& renderWindow);
    
    //ADDNEW2 not needed anymore
    //void showMoney(int money, RenderWindow& renderWindow);
    
    //ADDNEW passes an additional vector landlist
    void updateAnimations(vector<Defender*>& defenders, vector<Attacker*>& attackers, vector<Land*>& landList);
    
    //ADDNEW
    void handleTools(vector<Defender*>& defenders, vector<Land*>& landList, sf::RenderWindow& window);
    //ADDNEW
    void setBgMusic();
    
public:
    Game(sf::Vector2f windowSize);
    int run(RenderWindow& renderWindow);
    unsigned int getScore() const { return score; }
    //ADDNEW : this shouldnt be needed-
    //void toggleMuteSfx();
    //ADDNEW
    void toggleMuteMusic();
    
    void increaseDifficulty() { difficulty++; }
    void decreaseDifficulty() { difficulty--; }
};

#endif /* Game_hpp */

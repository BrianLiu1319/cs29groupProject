#pragma once

#include "Attacker.hpp"
#include "Coin.hpp"
#include "Collider.hpp"
#include "Defender.hpp"
#include "FolderPath.hpp"
#include "Inventory.hpp"
#include "Land.hpp"
#include "Menu.hpp"
#include "Toolbar.hpp"
#include "ValueDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace sf;

class Game : public Menu {
    // NOTE: go to Folder.hpp to change the folder path
private:
  const string path = assetFolder + "dogSprites.png";
  const std::string clickSFXPath01 = assetFolder + "click02.wav";
  const std::string bgMusicPath = assetFolder + "background music.wav";
  const std::string bgTexturePath = assetFolder + "game background-01.png";

  const int widthOfLand = 74;
  const int heightOfLand = 94;
  int money = 200;
  unsigned int score = 0;
  float animationDeltaTime = 0.0f;
  bool gaming = false;
  float deltaGenTime = 0.0f;
  float waveGenTime = 0.0f;
  bool waveStart = false;
  int numDogsInBigWave = 0;
  int currentWave = 1;
  bool muteMusic = false;
  bool onWave = false;
  bool gameOver = false;
  int difficulty = 1;

  Mutex threadLock;
  sf::Clock generatorClock;
  ValueDisplay statsDisplay;
  sf::Music bgMusic;
  Toolbar tools;
  sf::Clock animationClock;
  Font font1;
  Event event;

  vector<Land*> genrateLandList();
  vector<Inventory*> generateInvenList();


  void addAttacker(vector<Attacker *> &attackers, sf::Vector2f a);
  void gameClock(RenderWindow &window, vector<Collider *> &things);
  void checkCollision(vector<Attacker *> &attackers, vector<Bullet *> &bullets,
                      vector<Defender *> &defenders, vector<Coin *> &coins);
  void simpleAttackerGenerator(vector<Attacker *> &attackers,
                               const vector<Land *> &landList);


  void drawBuiltDefender(vector<Defender *> builtTowerList,
                         RenderWindow &renderWindow);

  void updateAnimations(vector<Defender *> &defenders,
                        vector<Attacker *> &attackers,
                        vector<Land *> &landList);
  void handleTools(vector<Defender *> &defenders, vector<Land *> &landList,
                   sf::RenderWindow &window);
  void setBgMusic();

public:
  Game(sf::Vector2f windowSize);
  int run(RenderWindow &renderWindow);
  unsigned int getScore() const { return score; }
  void toggleMuteMusic();

  void increaseDifficulty() { difficulty++; }
  void decreaseDifficulty() { difficulty--; }
};


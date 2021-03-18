#pragma once

#include "Animation.hpp"
#include "Coin.hpp"
#include "FolderPath.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Audio.hpp>
#include <ostream>

using namespace std;
using namespace sf;

static const string bulSpritePath = assetFolder + "bul.png";
static const string bulSpritePath1 = assetFolder + "bul1.png";
static const string catSpritePath = assetFolder + "catSprites1.png";
static const string towerSpritePath = assetFolder + "tower.png";
static const string dogeTower = assetFolder + "dogSprites.png";
static const string dogeTower2 = assetFolder + "dogSprites2.png";
static const string dogeTower1 = assetFolder + "dogSprites3.png";
static const unsigned WINDOW_WIDTH = 1280;
static const unsigned WINDOW_HEIGHT = 720;

const int MONEYMAKERCOST = 20;
const int MONEYPERCOIN = 10;

namespace DIR {
enum class DIRECTION { LEFT, RIGHT, TWR };
}


class Collider : public Sprite {
    // Collider Base Class
protected:
  int health = 0;
  float speed = 0.f;
  int cost = 40;
  bool status = true;
  bool isMaker = false;
  Texture textureOfObject{ Texture() };
  string spritePath;
  DIR::DIRECTION defaultDirection = DIR::DIRECTION::TWR;
  Vector2f position;

  Collider() = default;
  Collider(const string &textureFileName, DIR::DIRECTION direction,
           Vector2f positionOfObj = {0, 0}, int objHealth = 100,
           float objSpeed = 60.0f);
  Collider(const Texture &textureTemp, DIR::DIRECTION direction,
           Vector2f positionOfObj, int objHealth = 20, float objSpeed = 60.0f);

  friend ostream &operator<<(ostream &os, const Collider &collider);
  string typeName() const;
  ~Collider() override { cout << "Collider Destructor" << endl; }
  void autoTravel(DIR::DIRECTION direction);

public:
  void setStatus() { status = false; };
  bool getStatus() { return status; };
  int getHealth() const { return health; };
  float getSpeed() const { return speed; };
  virtual void animate(){}; // animate object
  void setDirection(DIR::DIRECTION ab) { defaultDirection = ab; }
  virtual void hurt(Collider &other);
  virtual void
  updateObject();
  bool getMaker() { return isMaker; }
  int getCost() { return cost; }
  virtual int howmanyCoininBox() { return 0; }
  virtual void drawCoins(RenderWindow &rn) { cout << "no coins" << endl; }
};

class Bullet : public Collider {
    // Bullet Derived class
  const std::string bulletSfxFile = assetFolder + "bullet sfx.wav";
  sf::SoundBuffer bulletSfxBuffer;
  sf::Sound bulletSfx;
  void setSfx();

public:
  Bullet() : Collider(bulSpritePath, DIR::DIRECTION::RIGHT, {25, 360}, 25) {
    scale(0.3f, 0.3f);
    setSfx();
  }
  Bullet(sf::Vector2f a)
      : Collider(bulSpritePath, DIR::DIRECTION::RIGHT, a, 50) {
    scale(0.3f, 0.3f);
    setSfx();
  }
  Bullet(const sf::Texture &temp, sf::Vector2f a)
      : Collider(temp, DIR::DIRECTION::RIGHT, a) {
    scale(0.3f, 0.3f);
    setSfx();
  }
  Bullet(const sf::Texture &temp, sf::Vector2f a, int b)
      : Collider(temp, DIR::DIRECTION::RIGHT, a, 50) {
    scale(0.3f, 0.3f);
    setSfx();
  }

  void playSfx() { bulletSfx.play(); }

};

class coinMaker : public Collider {
    // CoinMaker Class
private:
  int period = 0;

  vector<Coin *> coins = {};
  int cost = MONEYMAKERCOST;

  bool bGenerate = true;
  bool bCheck = true;

  Thread *m_pGenerate = nullptr; // generating thread
  Thread *m_pCheck = nullptr;    // checking thread
  Mutex mMutex;

public:
  coinMaker() = default;
  coinMaker(Vector2f pt) {
    string path = assetFolder + "coinMaker.png";
    if (!textureOfObject.loadFromFile(path, sf::IntRect(0, 0, 77, 94))) {
      std::cout << "erro" << std::endl;
    }
    setTexture(textureOfObject);
    setPosition(pt.x, pt.y);
    position = pt;
    setTextureRect(IntRect(0, 0, 77, 94));

    m_pGenerate = new Thread(coinMaker::gernateCoin, this);
    m_pGenerate->launch();
    m_pCheck = new Thread(coinMaker::checkLive, this);
    m_pCheck->launch();
    isMaker = true;
  };

  ~coinMaker() {
    bGenerate = false;
    bCheck = false;
  }
  int getCost() { return cost; }
  int howmanyCoininBox() { return static_cast<int>(coins.size()); }
  void drawCoins(RenderWindow &renderWindow) {
    mMutex.lock();

    for (int i = 0; i < static_cast<int>(coins.size()); i++) {
      //Coin *pCoin = coins[i];
      renderWindow.draw(coins[i]->getSp());
    }
    mMutex.unlock();
  }
  int clearCoin() {

    int counter = static_cast<int>(coins.size());
    Coin *pCoin = coins[0];
    int value = pCoin->getMoney();

    int money = counter * value; 
                      

    coins.clear(); 
    return money;
  }

  static void gernateCoin(coinMaker *pThis) {
    // thread
    while (pThis->bGenerate) {
      for (int i = 0; i < 80; i++) 
      {
        if (!pThis->bGenerate)
          break;
        sleep(milliseconds(100));
      }
      if (!pThis->bGenerate)
        break;
      if (pThis->coins.size() < 1) {
        Coin *pCoin = new Coin(pThis->position);
        pThis->mMutex.lock();
        pThis->coins.push_back(pCoin);
        pThis->mMutex.unlock();
      }
    }
  }
  static void checkLive(coinMaker *pThis) {
    while (pThis->bCheck) {

      pThis->mMutex.lock();
      if (pThis->coins.size() > 0) {
        for (vector<Coin *>::iterator it = pThis->coins.end() - 1;
             it != pThis->coins.begin(); it--) {
          Coin *pCoin = *it;
          pCoin->StepIt();
          if (pCoin->getLive() <= 0) {
            delete pCoin;
            pThis->coins.erase(it);
          }
        }
      }
      pThis->mMutex.unlock();
      sleep(milliseconds(3000));
    }
  }
};

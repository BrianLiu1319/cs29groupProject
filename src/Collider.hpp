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
static const string catSpritePath = assetFolder + "catSprites1.png";
static const string dogeTower = assetFolder + "dogSprites.png";
static const string dogeTower2 = assetFolder + "dogSprites2.png";
static const string dogeTower1 = assetFolder + "dogSprites3.png";
static const unsigned WINDOW_WIDTH = 1280;

namespace DIR {
enum class DIRECTION { LEFT, RIGHT, TWR };
}


class Collider : public Sprite {
protected:
	int health = 0;
	float speed = 0.f;
	bool status = true;
	Texture textureOfObject {Texture()};
	DIR::DIRECTION defaultDirection = DIR::DIRECTION::TWR;

	Collider() = default;
	Collider(const string &textureFileName,
	  DIR::DIRECTION direction,
	  Vector2f positionOfObj = {0, 0},
	  int objHealth = 100,
	  float objSpeed = 60.0f);
	Collider(const Texture &textureTemp,
	  DIR::DIRECTION direction,
	  Vector2f positionOfObj,
	  int objHealth = 20,
	  float objSpeed = 60.0f);

	friend ostream &operator<<(ostream &os, const Collider &collider);
	string typeName() const;
	void autoTravel(DIR::DIRECTION direction);

public:
	void setStatus() { status = false; };
	bool getStatus() const { return status; };
	int getHealth() const { return health; };
	float getSpeed() const { return speed; };
	void setDirection(DIR::DIRECTION ab) { defaultDirection = ab; }
	virtual void hurt(Collider &other);
	virtual void updateObject();
	~Collider() = default;
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
	explicit Bullet(sf::Vector2f a) : Collider(bulSpritePath, DIR::DIRECTION::RIGHT, a, 50) {
		scale(0.3f, 0.3f);
		setSfx();
	}
	Bullet(const sf::Texture &temp, sf::Vector2f a) : Collider(temp, DIR::DIRECTION::RIGHT, a) {
		scale(0.3f, 0.3f);
		setSfx();
	}
	Bullet(const sf::Texture &temp, sf::Vector2f a, int b) :
	    Collider(temp, DIR::DIRECTION::RIGHT, a, 25 * b) {
		scale(0.3f, 0.3f);
		setSfx();
	}

	void playSfx() { bulletSfx.play(); }
};

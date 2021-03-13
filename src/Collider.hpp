#ifndef COLLIDER_H
#define COLLIDER_H
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>

using namespace std;
using namespace sf;

static const unsigned WINDOW_WIDTH = 1280;
static const unsigned WINDOW_HEIGHT = 720;

enum DIRECTION { LEFT, RIGHT, TWR };

/// @brief
/// Base Class for all dynamic game objects
/// Derived from \class sf::Sprite
class Collider : public Sprite {
protected:
	int health;
	float speed;
	DIRECTION defaultDirection;
/**
 * @brief Main Constructor for Collider
 * @param texture = constant sf::Texture address
 * @param direction	= enum (LEFT,RIGHT,TWR)
 * @param coordinate = sf::Vector<2f>(x,y)
 * @param objHealth = Health of object
 * @param objSpeed = Speed of Object
 */
	Collider(const Texture &texture,
	  DIRECTION direction,
	  Vector2f coordinate,
	  int objHealth = 10,
	  float objSpeed = 60.0f);
	// animate object
	virtual void animate() {};
	/// @brief Change location of the object based on
	/// @param direction enum
	void autoTravel(DIRECTION direction);

public:
	int getHealth() const { return health; }
	/// @brief	sets a new direction for object
	/// @param new DIRECTION enum value
	void setDirection(DIRECTION newDir) { defaultDirection = newDir; }
	virtual void hurt(Collider &other);
	virtual void updateObject();  // call funcs to calculate or whatever is needed to be done
};

/**
 * @brief  Bullet derived from Collider
 */
class Bullet : public Collider {
public:
	/**
	 * @brief Main Constructor for Bullet
	 * @param temp = address of Bullet Texture
	 * @param spawnLocation = sf::Vector<2f>(x,y) coordiantes
	 */
	Bullet(const Texture &temp, Vector2f spawnLocation) : Collider(temp, RIGHT, spawnLocation, 25) {
		scale(0.05, 0.05);
		speed = 15;
	}
};

/**
 * @brief Attacker derived from Collider
 */
class Attacker : public Collider {
public:
	//	void hurt(Collider &other) override;
	Attacker(const Texture &catTexture, Vector2f loc) :
	    Collider(catTexture, LEFT, {WINDOW_WIDTH+10, loc.y}, 100, 10.0f) {
		scale(0.5, 0.5);
	};
};

/**
 * @brief Defender derived from Collider
 */
class Defender : public Collider {
public:
	void fire(vector<Bullet *> &bulletsList, const Texture &bulletTexture);
	Defender(const Texture &towerTexture, Vector2f loc) :
	    Collider(towerTexture, TWR, {loc.x, loc.y}, 100, 0) {
		scale(0.5, 0.5);
	};
};


/**
 * @brief All texture object that holds textures
 * @param const string bulSpritePath
 * @param const string catSpritePath
 * @param const string towerSpritePath
 * @param const string landSpritePath
 * @param const string landSpritePath2
 * @param const string inventoryPath
 */
class AllTextures {
	const string bulSpritePath = "assets/bul.png";
	const string catSpritePath = "assets/cat1.png";
	const string towerSpritePath = "assets/doge.png";
	const string landSpritePath = "assets/grass.jpg";
	const string landSpritePath2 = "assets/grass2.jpg";
	const string inventoryPath = "assets/inv.png";
	Texture *bullet;
	Texture *tower;
	Texture *attacker;
	Texture *land;
	Texture *land2;
	Texture *inv;

public:
	AllTextures();
	~AllTextures() {
		delete bullet;
		delete tower;
		delete attacker;
		delete land;
		delete land2;
		delete inv;
	}
	Texture &getBullet() const { return *bullet; }
	Texture &getTower() const { return *tower; }
	Texture &getAttacker() const { return *attacker; }
	Texture &getLand() const { return *land; }
	Texture &getLand2() const { return *land2; }
	Texture &getInv() const { return *inv; }
};

/**
 * @brief Land object
 * @var bool empty = bool tells if empty
 * @var Texture image = Texture of the object
 * @var Sprite spLand Sprite of the object
 */
class Land {
	bool empty;
	Texture image;
	Sprite spLand;
public:
	/**
	 * @brief Land Constructor
	 * @param num = type of grid
	 * @param point = coordinate of sf::Vector<2f>(x,y)
	 * @param texture = Pointer to Alltextures obj
	 */
	Land(int num, Vector2f point, AllTextures *texture);
	Sprite getSprite() { return spLand; }
	Vector2f getPositionofLand();
	void setEmpty(bool em) { empty = em; }
	bool getEmpty() const { return empty; }
};


#endif

#include "Collider.hpp"

/// @brief spawn location offset for bullet
const short BULLET_OFFSET = 5;

/**
 * @brief Collider main constructor
 * @param texture of obj
 * @param direction enum hold direction
 * @param coordinate Vector2f(x,y)
 * @param objHealth health of the obj
 * @param objSpeed speed of the obj
 */
Collider::Collider(const Texture &texture,
  DIRECTION direction,
  Vector2f coordinate,
  int objHealth,
  float objSpeed) {
	speed = objSpeed;
	health = objHealth;
	setTexture(texture);

	Vector2f origin(getGlobalBounds().width / 2.0f, getGlobalBounds().height / 2.0f);
	setOrigin(origin);
	defaultDirection = direction;
	setPosition(coordinate.x, coordinate.y);
	// Resize(20.0f, 20.0f); // Problem: Need to work on scaling the sprite
	// somehow.
}

/**
 * @brief Automatic increment of position based on
 * \enum DIRECTION
 * @param direction
 */
void Collider::autoTravel(DIRECTION direction) {
	if (direction == DIRECTION::RIGHT)
		this->move(((0.1f) * speed), 0.0f);
	else if (direction == DIRECTION::LEFT)
		this->move(((-0.1f) * speed), 0.0f);
}

/**
 * @brief Removes the health of the attacker form the &other
 * @param other = address of the Collider got hurt
 */
void Collider::hurt(Collider &other) {
	cout << "Health Before :" << other.health << endl;
	other.health -= health;
	cout << "Health After :" << other.health << endl;
	// if (health == other.health) other.health = 0; Removed since it took enemies
	// out early.
}

/**
 * @brief Animates and call the autotravel function
 */
void Collider::updateObject() {
	this->animate();
	if (defaultDirection == DIRECTION::LEFT)
		autoTravel(DIRECTION::LEFT);
	else if (defaultDirection == DIRECTION::RIGHT)
		autoTravel(DIRECTION::RIGHT);
}

/**
 * @brief Triggers a defender to place a bullet in to the allbullets vector
 * @param bulletsList = address of all bullets vectors
 * @param bulletTexture = texture of the bullet
 */
void Defender::fire(vector<Bullet *> &bulletsList, const Texture &bulletTexture) {
	auto point = this->getPosition();
	point.y += BULLET_OFFSET;  // offset for bullet
	auto *temp = new Bullet(bulletTexture, point);
	bulletsList.push_back(temp);
}

/**
 * @brief Inits all textures
 */
AllTextures::AllTextures() {
	auto b = new Texture;
	b->loadFromFile(bulSpritePath);
	auto t = new Texture;
	t->loadFromFile(towerSpritePath);
	auto a = new Texture;
	a->loadFromFile(catSpritePath);
	auto l = new Texture;
	l->loadFromFile(landSpritePath);
	auto l2 = new Texture;
	l2->loadFromFile(landSpritePath2);
	auto in = new Texture;
	in->loadFromFile(inventoryPath);

	bullet = b;
	tower = t;
	attacker = a;
	land = l;
	land2 = l2;
	inv = in;
}

/**
 * @brief The object that makes the grid
 * @param num = for diff of texture
 * @param point coordinates for placing
 * @param texture of the object
 */
Land::Land(int num, Vector2f point, AllTextures *texture) {
	if ((num + 1) % 2 == 0) {
		spLand.setTexture(texture->getLand());
	} else
		spLand.setTexture(texture->getLand2());
	spLand.setPosition(point);
	spLand.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
	spLand.setTextureRect(IntRect(0, 0, 77, 94));
	empty = true;
	// spLand.setScale(Vector2f(0.5, 0.5));
}

/**
 * @brief Returns the midpoint of the grid
 * @return Vector2f(x,y)
 */
Vector2f Land::getPositionofLand() {
	auto offset = Vector2f({spLand.getLocalBounds().width / 2, spLand.getLocalBounds().height / 2});
	auto temp = spLand.getPosition() + offset;
	return temp;
}

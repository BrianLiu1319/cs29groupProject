#include "Collider.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <iostream>

const short BULLET_OFFSET = 5;  // change this for number for bullet spawn location

Collider::Collider(const Texture &textureTemp,
  DIRECTION direction,
  Vector2f positionOfObj,
  int objHealth,
  float objSpeed) {
	speed = objSpeed;
	health = objHealth;
	setTexture(textureTemp);

	Vector2f origin(getGlobalBounds().width / 2.0f, getGlobalBounds().height / 2.0f);
	setOrigin(origin);
	defaultDirection = direction;
	setPosition(positionOfObj.x, positionOfObj.y);
	// Resize(20.0f, 20.0f); // Problem: Need to work on scaling the sprite
	// somehow.
}

void Collider::autoTravel(DIRECTION direction) {
	if (direction == RIGHT)
		this->move(((0.1f) * speed), 0.0f);
	else if (direction == LEFT)
		this->move(((-0.1f) * speed), 0.0f);
}

void Collider::hurt(Collider &other) {
	cout << "Health Before :" << other.health << endl;
	other.health -= health;
	cout << "Health After :" << other.health << endl;
	// if (health == other.health) other.health = 0; Removed since it took enemies
	// out early.
}

void Collider::updateObject() {
	this->animate();
	if (defaultDirection == LEFT)
		autoTravel(LEFT);
	else if (defaultDirection == RIGHT)
		autoTravel(RIGHT);
	/*
	        if ((dynamic_cast<Attacker*>(this)) != nullptr) autoTravel(LEFT);
	        else if ((dynamic_cast<Bullet*>(this)) != nullptr) autoTravel(RIGHT);
	*/
}

/*
void Bullet::hurt(Collider &other) {
        cout << "Bullet OUCH" << endl;
//	other.hurt(*this);
}
void Attacker::hurt(Collider &other) {

        // if (health == 0 ) dead
}*/

void addAttacker(vector<Attacker *> &attackers, const Texture &attackerText, Vector2f loc) {
	auto temp = new Attacker(attackerText,loc);
	attackers.push_back(temp);
}

void addTower(vector<Defender *> &towers, const Texture &defText, Vector2f loc) {
	auto temp = new Defender(defText,loc);
	towers.push_back(temp);
}

void Defender::fire(vector<Bullet *> &bulletsList, const Texture &bulletTextrue) {
	auto point = this->getPosition();
	point.y += BULLET_OFFSET;  // offset for bullet
	auto *temp = new Bullet(bulletTextrue, point);
	bulletsList.push_back(temp);
}

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

	bullet = b;
	tower = t;
	attacker = a;
	land = l;
	land2 = l2;
}

Land::Land(int num, Vector2f o, AllTextures *texture) {
	if ((num + 1) % 2 == 0) {
		spLand.setTexture(texture->getLand());
	}else
	spLand.setTexture(texture->getLand2());
	spLand.setPosition(o);
	spLand.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
	spLand.setTextureRect(IntRect(0, 0, 77, 94));
	empty = true;
	// spLand.setScale(Vector2f(0.5, 0.5));
}

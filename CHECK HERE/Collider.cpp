#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "Collider.h"

ostream& operator <<(ostream& os, const Collider& collider) {
	os << collider.typeName() << " :" << /*"uid: " << collider.uid <<*/  " health: "
		<< collider.health << " speed: " << collider.speed
		<< " Origin: X:" << collider.getOrigin().x << " Y:" << collider.getOrigin().y;
	return os;
}

Collider::Collider(const string& textureFileName, DIRECTION direction, Vector2f positionOfObj, int objHealth, float objSpeed) {
	speed = objSpeed;
	health = objHealth;
	if (!(textureOfObject.loadFromFile(textureFileName))) cerr << "Can not load texture file " << endl;
	setTexture(textureOfObject);

	Vector2f origin(getGlobalBounds().width / 2.0f, getGlobalBounds().height / 2.0f);
	setOrigin(origin);
	defaultDirection = direction;
	setPosition(positionOfObj.x, positionOfObj.y);
	//Resize(20.0f, 20.0f); // Problem: Need to work on scaling the sprite somehow. 
}

Collider::Collider(const Texture& textureTemp, DIRECTION direction, Vector2f positionOfObj, int objHealth, float objSpeed) {
	speed = objSpeed;
	health = objHealth;
	setTexture(textureTemp);

	Vector2f origin(getGlobalBounds().width / 2.0f, getGlobalBounds().height / 2.0f);
	setOrigin(origin);
	defaultDirection = direction;
	setPosition(positionOfObj.x, positionOfObj.y);
	//Resize(20.0f, 20.0f); // Problem: Need to work on scaling the sprite somehow. 
}

string Collider::typeName() const {
	string shapeName = typeid(*this).name();
#ifdef _MSC_VER       // for MS Visual Studio
	shapeName = shapeName.substr(6);
#else                 // for other compilers
	shapeName = shapeName.substr(shapeName.find_first_not_of("0123456789"));
#endif
	return shapeName;
}

void Collider::autoTravel(DIRECTION direction) {
	cout << this->typeName() << " x :" << this->getPosition().x << endl;
	if (direction == RIGHT) this->move(((0.1f) * speed), 0.0f);
	else if (direction == LEFT) this->move(((-0.1f) * speed), 0.0f);
}

void Collider::hurt(Collider& other) {
	cout << typeName() << "OUCH" << endl;
	cout << "Health Before :" << other.health << endl;
	other.health -= health;
	cout << "Health After :" << other.health << endl;
	// if (health == other.health) other.health = 0; Removed since it took enemies out early. 
}

void Collider::updateObject() {
	this->animate();
	if (defaultDirection == LEFT) autoTravel(LEFT);
	else if (defaultDirection == RIGHT) autoTravel(RIGHT);
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


void addAttacker(vector<Attacker*>& attackers) {
	auto* temp = new Attacker();
	attackers.push_back(temp);
}

void addAttacker(vector<Attacker*>& attackers, Vector2f a) {
	auto* temp = new Attacker(a);
	attackers.push_back(temp);
}

/*
void addBullet(vector<Bullet*>& things) {
	cout << "Adding the new boi" << endl;
	auto* temp = new Bullet();
	things.push_back(temp);
}
*/

void addBullet(vector<Bullet*>& things, Bullet* a) {
	Bullet* temp = a;
	things.push_back(temp);
}

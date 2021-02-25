#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "Collider.hpp"

ostream &operator <<(ostream &os, const Collider &collider) {
	os << collider.typeName() << " :" << /*"uid: " << collider.uid <<*/  " health: "
	   << collider.health << " speed: " << collider.speed
	   << " Origin: X:" << collider.getOrigin().x << " Y:" << collider.getOrigin().y;
	return os;
}

Collider::Collider(const string &textureFileName,DIRECTION direction) {
	if (!(textureOfObject.loadFromFile(textureFileName))) cerr << "Can not load texture file " << endl;
		setTexture(textureOfObject);
	Vector2f origin(getGlobalBounds().width / 2.0f,getGlobalBounds().height / 2.0f );
	setOrigin(origin);
	defaultDirection = direction;
	
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
	cout << this->typeName() <<" x :" << this->getPosition().x << endl;
	if (direction == RIGHT) this->move((0.1f)*speed, 0.0f);
	else if (direction == LEFT) this->move((-0.1f)*speed, 0.0f);
}

void Collider::hurt(Collider &other) {
	cout << this->typeName() <<"OUCH" << endl;
	cout << "Health Before :" << getHealth() << endl;
	this->health -= other.getHealth();
	cout << "Health After :" << getHealth() << endl;
}

void Collider::updateObject() {
	this->animate();
	if ((dynamic_cast<Attacker*>(this)) != NULL) autoTravel(LEFT);
	else if ((dynamic_cast<Bullet*>(this)) != NULL) autoTravel(RIGHT);

}

/*
void Bullet::hurt(Collider &other) {
	cout << "Bullet OUCH" << endl;
//	other.hurt(*this);
}

void Attacker::hurt(Collider &other) {
	
	// if (health == 0 ) dead
}*/

void addAttacker(RenderWindow &window, vector<Attacker*> &attackers) {
	auto* temp = new Attacker();
	temp->setPosition((4 * window.getSize().x / 5), (window.getSize().y / 2));
//	temp->scale(0.4, 0.4);
	attackers.push_back(temp);
}

void addBullet(RenderWindow &window, vector<Bullet*> &bullets) {
	auto* temp = new Bullet();
	temp->setPosition((window.getSize().x / 5), (window.getSize().y / 2));
	temp->scale(0.4, 0.4);
	bullets.push_back(temp);
}
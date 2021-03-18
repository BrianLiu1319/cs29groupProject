#include "Defender.hpp"

Defender::Defender(sf::Vector2f a) :
    Collider(dogeTower1, DIR::DIRECTION::RIGHT, {a.x, a.y + 47.0f}, 100, 0.0f),
    animator(dogeTower1, sf::Vector2u(4, 2), 1.0f / 3.0f), landIndex(0) {
	scale(0.5, 0.5);
	Vector2f origin(0, getGlobalBounds().height / 2.0f);
	setOrigin(origin);

	try {
		if (!barkSfxBuffer.loadFromFile(barkFile)) { throw barkFile; }
		if (!defeatSfxBuffer.loadFromFile(defeatFile)) { throw defeatFile; }
		barkSfx.setBuffer(barkSfxBuffer);
		barkSfx.setVolume(50.0f);
		defeatSfx.setBuffer(defeatSfxBuffer);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: HowToPlay" << std::endl;
		exit(1);
	}
}

Defender::Defender(sf::Vector2f a, float b) :
    Collider(dogeTower2, DIR::DIRECTION::RIGHT, {a.x, a.y + 47.0f}, 660, 0.0f),
    animator(dogeTower2, sf::Vector2u(4, 2), 1.0f / 3.0f), landIndex(0) {
	scale(0.5, 0.5);
	Vector2f origin(0, getGlobalBounds().height / b);
	setOrigin(origin);
	cost = 60;

	try {
		if (!barkSfxBuffer.loadFromFile(barkFile)) { throw barkFile; }
		if (!defeatSfxBuffer.loadFromFile(defeatFile)) { throw defeatFile; }
		barkSfx.setBuffer(barkSfxBuffer);
		barkSfx.setVolume(50.0f);
		defeatSfx.setBuffer(defeatSfxBuffer);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: HowToPlay" << std::endl;
		exit(1);
	}
}

Defender::Defender(sf::Vector2f a, int b) :
    Collider(dogeTower, DIR::DIRECTION::RIGHT, {a.x, a.y + 47.0f}, 100 * b, 0.0f),
    animator(dogeTower, sf::Vector2u(4, 2), 1.0f / 3.0f), landIndex(0) {
	scale(0.5, 0.5);
	Vector2f origin(0, getGlobalBounds().height / 2.0f);
	setOrigin(origin);
	cost = 80;

	try {
		if (!barkSfxBuffer.loadFromFile(barkFile)) { throw barkFile; }
		if (!defeatSfxBuffer.loadFromFile(defeatFile)) { throw defeatFile; }
		barkSfx.setBuffer(barkSfxBuffer);
		barkSfx.setVolume(50.0f);
		defeatSfx.setBuffer(defeatSfxBuffer);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: HowToPlay" << std::endl;
		exit(1);
	}
}

/*
Update the direction of the object
*/
void Defender::updateObject() {
	if (defaultDirection == DIR::DIRECTION::LEFT)
		autoTravel(DIR::DIRECTION::LEFT);
	else if (defaultDirection == DIR::DIRECTION::RIGHT)
		autoTravel(DIR::DIRECTION::RIGHT);
}

/**************
Updates the current frame
 of the animation.
**************/
void Defender::updateAnimation(float deltaTime) {
	animator.update(deltaTime);
	setTextureRect(animator.uvRect);
}

/**************
 Returns true if the Defender
 has been defeated
 AND the defeat animation
 has stopped playing.
 Returns false otherwise.
 **************/
bool Defender::isDefeated() const {
	if (currState == STATES::defeated && animator.isLastFrame()) { return true; }
	return false;
}

/**************
Sets the Defender to be defeated.
 Switches the animation to
 the defeat animation and prevents
 it from looping.
**************/
void Defender::setDefeated() {
	currState = STATES::defeated;
	animator.setLoop(false);
	animator.setActiveRow(1);
}

/*
Play a dog bark on spawn
*/
void Defender::bark() { barkSfx.play(); }

/*
play a sad sound on death
*/
void Defender::sadSound() { defeatSfx.play(); }

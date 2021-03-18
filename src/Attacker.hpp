#pragma once

#include "Collider.hpp"

class Attacker : public Collider {
	// NOTE: go to Folder.hpp to change the folder path
private:
	const std::string meowFile = assetFolder + "cat meow.wav";
	const std::string defeatFile = assetFolder + "cat defeat.wav";
	sf::SoundBuffer meowSfxBuffer, defeatSfxBuffer;
	sf::Sound meowSfx, defeatSfx;

	Animation animator;
	enum class STATES { moving, defeated };
	STATES currState = STATES::moving;

	void setSfx();
	void attack() {}

public:
	Attacker();
	Attacker(sf::Vector2f a);
	Attacker(sf::Vector2f a, string b);

	void updateAnimation(float deltaTime);
	void updateObject();
	void setDefeated();
	void setMoving();
	void meow();
	void sadSound();

	bool isDefeated() const;

	bool isOnDefeat() const {
		if (currState == STATES::defeated)
			return true;
		else
			return false;
	}
};

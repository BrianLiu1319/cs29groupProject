#pragma once


#include "Collider.hpp"

class Defender : public Collider {
	int cost = 40;
	// NOTE: go to Folder.hpp to change the folder path
	const std::string barkFile = assetFolder + "dog bark.wav";
	const std::string defeatFile = assetFolder + "dog defeat.wav";
	sf::SoundBuffer barkSfxBuffer, defeatSfxBuffer;
	sf::Sound barkSfx, defeatSfx;
	Animation animator;

	enum class STATES { standing, defeated };
	STATES currState = STATES::standing;
	int landIndex;

public:
	explicit Defender(sf::Vector2f a);
	Defender(sf::Vector2f a, int b);
	Defender(sf::Vector2f a, float b);
	void updateAnimation(float deltaTime);
	void updateObject();
	int getCost() const { return cost; }
	bool isDefeated() const;
	void setDefeated();

	void setLandIndex(int i) { landIndex = i; }
	int getLandIndex() const { return landIndex; }

	void increaseHealth(unsigned h) { health += h; }

	void bark();
	void sadSound();
};

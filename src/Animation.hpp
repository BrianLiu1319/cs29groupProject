#pragma once


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Animation {
	// NOTE: go to Folder.hpp to change the folder path
private:
	unsigned numOfRows;
	unsigned activeRow;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
	unsigned *numOfSpritesInRow;
	bool loop;

public:
	Animation(const sf::Texture &texture, const sf::Vector2u &imageCount, float switchTime);
	Animation(const std::string &texturePath, const sf::Vector2u &imageCount, float switchTime);
	~Animation();
	sf::IntRect uvRect;

	void update(unsigned row, float deltaTime);
	void update(float deltaTime);
	void setNumOfSpritesInRow(unsigned row, unsigned num);
	void setActiveRow(unsigned row);
	bool isLastFrame() const;
	void setLoop(bool set);
};

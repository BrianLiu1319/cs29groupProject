#include "Animation.hpp"

/*********************************
Constructor.
 Same as the other constructor,
 except that it accepts the texture path
 instead of a texture. It loads the texture
 itself.
*********************************/
Animation::Animation(const std::string &texturePath,
  const sf::Vector2u &imageCount,
  float switchTime) {
	sf::Texture texture;
	if (!texture.loadFromFile(texturePath)) {
		std::cerr << "Unable to load file " << texturePath << std::endl;
		exit(1);
	}

	numOfRows = imageCount.y;
	this->switchTime = switchTime;
	activeRow = 0;
	loop = true;
	totalTime = 0.0f;
	currentImage.x = 0;
	numOfSpritesInRow = new unsigned[imageCount.y];
	for (int i = 0; i < static_cast<int>(imageCount.y); i++) {
		numOfSpritesInRow[i] = imageCount.x;
	}
	uvRect.width = static_cast<int>(
	  static_cast<float>(texture.getSize().x) / static_cast<float>(imageCount.x));
	uvRect.height = static_cast<int>(
	  static_cast<float>(texture.getSize().y) / static_cast<float>(imageCount.y));
}

/*********************************
Updates the uvRect based on how much
 time has passed. Also updates the
 active row.
*********************************/
void Animation::update(unsigned row, float deltaTime) {
	// check if row is beyond the number of rows
	if (row > numOfRows) { row = 0; }

	if (row != activeRow) {
		activeRow = row;
		currentImage.x = 0;
	}

	currentImage.y = activeRow;
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= numOfSpritesInRow[activeRow]) {
			if (loop)
				currentImage.x = 0;
			else
				currentImage.x = numOfSpritesInRow[activeRow] - 1;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

/*********************************
Updates the uvRect based on how much
 time has passed. Does not change the
 active row.
*********************************/
void Animation::update(float deltaTime) {
	currentImage.y = activeRow;
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= numOfSpritesInRow[activeRow]) {
			if (loop)
				currentImage.x = 0;
			else
				currentImage.x = numOfSpritesInRow[activeRow] - 1;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

/*********************************
Sets the currently active row.
*********************************/
void Animation::setActiveRow(unsigned row) {
	// check if row exceed number of rows
	if (row > numOfRows) { row = 0; }

	activeRow = row;
	currentImage.x = 0;
}

/*********************************
Returns whether or not the animation
 is currently on the last frame.
*********************************/
bool Animation::isLastFrame() const {
	if (currentImage.x == numOfSpritesInRow[activeRow] - 1) { return true; }
	return false;
}

/*********************************
Sets whether or not to loop the
 animation.
*********************************/
void Animation::setLoop(bool set) { loop = set; }

Animation::~Animation() { delete[] numOfSpritesInRow; }

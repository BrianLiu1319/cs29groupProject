#include "Animation.hpp"

/*********************************
Constructor.
 Gets the texture, the (x, y) image
 count, and the switch time.
 Calculates the size of the uvRect
 based on the size of the texture
 and the image count.
 Loop is set to true by default.
*********************************/
Animation::Animation(sf::Texture *texture,
  sf::Vector2u imageCount,
  float switchTime) {
	this->numOfRows = imageCount.y;
	this->switchTime = switchTime;
	activeRow = 0;
	loop = true;
	totalTime = 0.0f;
	currentImage.x = 0;
	numOfSpritesInRow = new unsigned[imageCount.y];
	for (unsigned int i = 0; i < imageCount.y; i++) {
		numOfSpritesInRow[i] = imageCount.x;
	}
	uvRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
	uvRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
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
Sets the number of sprites in
 a row. Used for when the number
 in a row is different from other
 rows.
*********************************/
void Animation::setNumOfSpritesInRow(unsigned row, unsigned num) {
	numOfSpritesInRow[row] = num;
}

/*********************************
Sets the currently active row.
*********************************/
void Animation::setActiveRow(unsigned row) {
	// check if row exceed number of rows
	if (row > numOfRows) { row = 0; }

	activeRow = row;
}

/*********************************
Returns whether or not the animation
 is currently on the last frame.
*********************************/
bool Animation::isLastFrame() {
	if (currentImage.x == numOfSpritesInRow[activeRow]) { return true; }
	return false;
}

/*********************************
Sets whether or not to loop the
 animation.
*********************************/
void Animation::setLoop(bool set) { loop = set; }

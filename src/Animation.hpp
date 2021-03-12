#ifndef Animation_hpp
#define Animation_hpp
#include <SFML/Graphics.hpp>

class Animation {
private:
	unsigned numOfRows;
	unsigned activeRow;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
	unsigned *numOfSpritesInRow;
	bool loop;

public:
	Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
	~Animation() = default;
	sf::FloatRect uvRect;
	void update(unsigned row, float deltaTime);
	void update(float deltaTime);
	void setNumOfSpritesInRow(unsigned row, unsigned num);
	void setActiveRow(unsigned row);
	bool isLastFrame();
	void setLoop(bool set);
};

#endif /* Animation_hpp */

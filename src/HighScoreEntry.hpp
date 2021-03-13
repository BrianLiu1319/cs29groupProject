#ifndef HighScoreEntry_hpp
#define HighScoreEntry_hpp

#include "Menu.hpp"
#include "Score.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class HighScoreEntry : public Menu {
private:
	// NOTE: go to Menu.hpp to change the folder path

	// File Names
	const std::string bgPath = assetFolder + "high score entry-01.png";
	const std::string confirmButtonPath = assetFolder + "confirm button.png";
	const std::string confirmButtonInvPath = assetFolder + "confirm button inverted.png";
	const std::string fontPath = assetFolder + "AnonymousPro-Regular.ttf";
	const std::string clickSFXPath01 = assetFolder + "click02.wav";

	sf::RectangleShape textBox, confirmButton, cursor;
	sf::Texture confirmButtonTexture, confirmButtonTextureInv;
	sf::Font inputTextFont;
	sf::Text inputText, maxLengthText;
	sf::Vector2f defaultCursorPos;
	Score score;
	std::string textTyped;
	float totalTime;
	float switchTime;
	bool cursorOn;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	HighScoreEntry(sf::Vector2f windowSize);
	void setConfirmButtonTexture(std::string path, std::string pathInv);
	void setFont(std::string path);
	int run(sf::Vector2f mousePos, float deltaTime);
	void enterText(char c);
	void setScoreValue(unsigned int s) { score.setScore(s); }
	Score getScore() const { return score; }
};


#endif /* HighScoreEntry_hpp */

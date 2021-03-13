#include "GameOver.hpp"

/*********************************
Draws the Game Over screen.
*********************************/
void GameOver::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(confirmButton);
	target.draw(text);
}

/*********************************
Constructor.
 Sets up everything according to the
 window size.
*********************************/
GameOver::GameOver(sf::Vector2f windowSize) : Menu(windowSize), score(0) {
	sf::Vector2f buttonSize(windowSize.x / 1920.0f * 600.0f, windowSize.y / 1080.0f * 135.0f);
	sf::Vector2f centerButtonPos(windowSize.x / 2.0f - buttonSize.x / 2,
	  windowSize.y / 2.0f - buttonSize.y / 2);

	background.setFillColor(sf::Color::Black);

	try {
		setConfirmButtonTexture(confirmButtonPath, confirmButtonInvPath);
		setFont(fontPath);
		setClickSound(clickSFXPath01);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open file " << fileName << std::endl;
		std::cerr << "Location: GameOver " << std::endl;
		exit(1);
	}

	setText();
	confirmButton.setSize(sf::Vector2f(buttonSize.x, buttonSize.y));
	confirmButton.setPosition(centerButtonPos.x, centerButtonPos.y);
	confirmButton.setOutlineThickness(buttonSize.y / 20.0f);
	text.setCharacterSize(static_cast<unsigned int>(windowSize.y / 18));
	text.setFillColor(sf::Color(242, 218, 0));
	text.setPosition(windowSize.x / 2.0f - buttonSize.x / 2.0f, windowSize.y * 0.3f);
}

/*********************************
Sets the texture for the confirm button.
 Throws the path of file if not found.
*********************************/
void GameOver::setConfirmButtonTexture(const std::string &path, const std::string &pathInv) {
	if (!confirmButtonTexture.loadFromFile(path.c_str())) { throw(std::string(path)); }
	if (!confirmButtonTextureInv.loadFromFile(pathInv.c_str())) { throw(std::string(pathInv)); }

	confirmButton.setTexture(&confirmButtonTexture);
}

/*********************************
Sets the font for the text.
 Throws the path of file if not found.
*********************************/
void GameOver::setFont(const std::string &path) {
	if (!textFont.loadFromFile(path.c_str())) { throw(std::string(path)); }
	text.setFont(textFont);
}

/*********************************
Sets the text to read:
 "Game Over...
 Your Score: (score)"
*********************************/
void GameOver::setText() { text.setString("Game Over...\nYour Score: " + std::to_string(score)); }

/*********************************
Runs the Game Over screen.
*********************************/
int GameOver::run(sf::Vector2f mousePos) {
	/*
	 state:
	 0 - Stay on Game Over screen
	 1 - Leave Game Over screen
	 */
	int state = 0;

	// Handle actions on confirm button
	if (handleButton(confirmButton, confirmButtonTexture, confirmButtonTextureInv, mousePos)) {
		state = 1;
		score = 0;
		setText();
	}

	return state;
}

/*********************************
Sets the score shown.
*********************************/
void GameOver::setScore(unsigned int s) {
	score = s;
	setText();
}

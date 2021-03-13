#include "HowToPlay.hpp"

/*********************************
 Draws the How To Play screen.
 *********************************/
void HowToPlay::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	if (page < maxPage - 1) target.draw(nextButton);
	if (page > 0) target.draw(prevButton);
	target.draw(backButton);
	target.draw(guidePage);
}

/*********************************
Constructor.
 Sets up everything according
 to the window size.
*********************************/
HowToPlay::HowToPlay(sf::Vector2f windowSize) : Menu(windowSize) {
	// Set the current page of the How To Play screen
	page = 0;

	// Calculate Button sizes and positions
	sf::Vector2f buttonSize(windowSize.y / 1080.0f * 135.0f, windowSize.y / 1080.0f * 135.0f);
	sf::Vector2f centerButtonPos(windowSize.x / 2.0f, windowSize.y / 2.0f - buttonSize.y / 2.0f);

	// Set up page
	guidePage.setSize(sf::Vector2f(windowSize.x / 3.0f * 2.0f, windowSize.y / 4.0f * 3.0f));
	guidePage.setPosition(windowSize.x / 2.0f - guidePage.getSize().x / 2.0f,
	  windowSize.y / 2.0f - guidePage.getSize().y / 2.0f);

	// Set Buttons
	nextButton.setSize(sf::Vector2f(buttonSize.x / 2, buttonSize.x));
	nextButton.setPosition(
	  sf::Vector2f(centerButtonPos.x + windowSize.x / 1920.0f * 800.0f - buttonSize.x / 2.0f,
	    centerButtonPos.y));
	nextButton.setOutlineThickness(buttonSize.y / 20.0f);
	prevButton.setSize(sf::Vector2f(buttonSize.x / 2, buttonSize.x));
	prevButton.setPosition(
	  sf::Vector2f(centerButtonPos.x - windowSize.x / 1920.0f * 800.0f, centerButtonPos.y));
	prevButton.setOutlineThickness(buttonSize.y / 20.0f);
	backButton.setSize(sf::Vector2f(buttonSize.y, buttonSize.y));
	backButton.setPosition(windowSize.x / 1920.0f * 20.0f, windowSize.x / 1920.0f * 20.0f);
	backButton.setOutlineThickness(buttonSize.y / 20.0f);


	// Set Textures
	try {
		// Set up the array for different pages of the guide
		for (int i = 0; i < maxPage; i++) {
			if (!guidePageTexture[i].loadFromFile(guidePagePath + std::to_string(i + 1) + ".png")) {
				throw(guidePagePath + std::to_string(i + 1) + ".png");
			}
		}
		setBgTexture(menuBackgroundTexturePath);
		setNextTexture(nextButtonPath, nextButtonInvPath);
		setPrevTexture(prevButtonPath, prevButtonInvPath);
		setBackTexture(backButtonPath, backButtonInvPath);
		setClickSound(clickSFXPath01);
		guidePage.setTexture(&guidePageTexture[page]);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: HowToPlay" << std::endl;
		exit(1);
	}
}

/*********************************
Sets the texture and inverse
 texture of the next button.
*********************************/
void HowToPlay::setNextTexture(const std::string &path, const std::string &pathInv) {
	if (!nextTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!nextTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }
	nextButton.setTexture(&nextTexture);
}

/*********************************
Sets the texture and inverse
 texture of the prev button.
*********************************/
void HowToPlay::setPrevTexture(const std::string &path, const std::string &pathInv) {
	if (!prevTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!prevTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }

	prevButton.setTexture(&prevTexture);
}

/*********************************
Sets the texture and inverse
 texture of the back button.
*********************************/
void HowToPlay::setBackTexture(const std::string &path, const std::string &pathInv) {
	if (!backTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!backTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }

	backButton.setTexture(&backTexture);
}

/*********************************
Runs the how to play screen.
*********************************/
int HowToPlay::run(sf::Vector2f mousePos) {
	/***
	 states:
	 0 - How To Play
	 1 - Back to Settings Menu
	 */
	int state = 0;

	// Handle actions on the next button.
	if (page < maxPage - 1 && handleButton(nextButton, nextTexture, nextTextureInv, mousePos)) {
		page++;
		guidePage.setTexture(&guidePageTexture[page]);
	}

	// Handle actions on the prev button.
	if (page > 0 && handleButton(prevButton, prevTexture, prevTextureInv, mousePos)) {
		page--;
		guidePage.setTexture(&guidePageTexture[page]);
	}

	// Handle actions on the back button.
	if (handleButton(backButton, backTexture, backTextureInv, mousePos)) {
		state = 1;
		page = 0;
		guidePage.setTexture(&guidePageTexture[page]);
	}

	return state;
}

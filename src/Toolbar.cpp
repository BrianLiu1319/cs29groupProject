#include "Toolbar.hpp"

void Toolbar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(whistleButton);
	target.draw(healthButton);
}

/**************
Constructor.
 Sets up everything according
 to the window size.
**************/
Toolbar::Toolbar(sf::Vector2f windowSize) : Menu(windowSize) {
	// Calculate sizes and positions
	sf::Vector2f buttonSize(windowSize.y / 1080.0f * 130.0f, windowSize.y / 1080.0f * 130.0f);
	sf::Vector2f centerButtonPos(windowSize.x / 2.0f, windowSize.y / 2.0f - buttonSize.y / 2.0f);

	// Set Textures
	try {
		setWhistleTexture();
		setHealthTexture();
		setClickSound(clickSFXPath01);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: Toolbar" << std::endl;
	}
	background.setFillColor(sf::Color::Transparent);

	// Set sizes and positions
	whistleButton.setSize(buttonSize);
	healthButton.setSize(buttonSize);
	whistleButton.setOutlineThickness(buttonSize.y / 20.0f);
	healthButton.setOutlineThickness(buttonSize.y / 20.0f);
	whistleButton.setOutlineColor(sf::Color::Transparent);
	healthButton.setOutlineColor(sf::Color::Transparent);
	whistleButton.setPosition(windowSize.x - buttonSize.x * 1.2f,
	  windowSize.y - buttonSize.y * 1.2f);
	healthButton.setPosition(windowSize.x - buttonSize.x * 1.2f * 2.0f,
	  windowSize.y - buttonSize.y * 1.2f);
}

/**************
Sets texture for the
 whistle button.
**************/
void Toolbar::setWhistleTexture() {
	if (!whistleTexture.loadFromFile(whistlePath)) { throw(std::string(whistlePath)); }
	if (!whistleTextureInv.loadFromFile(whistlePathInv)) { throw(std::string(whistlePathInv)); }

	whistleButton.setTexture(&whistleTexture);
}

/**************
Sets texture for the
 health button.
**************/
void Toolbar::setHealthTexture() {
	if (!healthTexture.loadFromFile(healthPath)) { throw(std::string(healthPath)); }
	if (!healthTextureInv.loadFromFile(healthPathInv)) { throw(std::string(healthPathInv)); }

	healthButton.setTexture(&healthTexture);
}

/**************
 Returns true if
 the whistle tool (for removing dogs)
 is currently selected.
 **************/
bool Toolbar::whistleSelected() {
	if (currentSelection == SELECTION::whistle) { return true; }
	return false;
}

/**************
Returns true if
the health tool (for boosting dog hp)
is currently selected.
**************/
bool Toolbar::healthSelected() {
	if (currentSelection == SELECTION::health) { return true; }
	return false;
}

/**************
Deselects all tools.
**************/
void Toolbar::deselectAll() {
	currentSelection = SELECTION::none;
	healthButton.setOutlineColor(sf::Color::Transparent);
	whistleButton.setOutlineColor(sf::Color::Transparent);
}

/**************
Runs the toolbar.
 Returns:
 0 - Nothing selected
 1 - Whistle selected
 2 - Health selected
**************/
int Toolbar::run(sf::Vector2f mousePos) {
	int state = 0;

	if (handleButton(whistleButton, whistleTexture, whistleTextureInv, mousePos)) {
		state = 1;
		currentSelection = SELECTION::whistle;
		whistleButton.setOutlineColor(sf::Color::White);
		healthButton.setOutlineColor(sf::Color::Transparent);
	} else if (handleButton(healthButton, healthTexture, healthTextureInv, mousePos)) {
		state = 2;
		currentSelection = SELECTION::health;
		healthButton.setOutlineColor(sf::Color::White);
		whistleButton.setOutlineColor(sf::Color::Transparent);
	}

	return state;
}

/**************
Overrides the handleButton function
 in parent class Menu,
 since the Toolbar is a special case
 in which a clicked tool
 should stay selected
 after the mouse leaves it.
**************/
bool Toolbar::handleButton(sf::RectangleShape &button,
  const sf::Texture &buttonTexture,
  const sf::Texture &buttonInvTexture,
  const sf::Vector2f &mousePos) {
	bool isClicked = false;

	if (isMouseOver(mousePos, button)) {
		/*********************************
		When mouse is hovering over
		 the button:
		*********************************/
		// button.setOutlineColor(sf::Color::White);
		button.setTexture(&buttonInvTexture);

		/*********************************
		When mouse clicks the button:
		*********************************/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseStartClick) {
			if (!muteSfx) click.play();
			mouseStartClick = false;
		} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseStartClick) {
			isClicked = true;
			// button.setOutlineColor(sf::Color::Transparent);
			button.setTexture(&buttonTexture);
			mouseStartClick = true;
		}

		/*********************************
		When mouse leaves the button:
		*********************************/
	} else if (button.getTexture() != &buttonTexture) {
		button.setTexture(&buttonTexture);
	}

	return isClicked;
}

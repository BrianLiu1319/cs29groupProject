#include "Menu.hpp"

/*************
 Draw the Menu
 */
void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
}

Menu::Menu(sf::Vector2f windowSize) {
	background.setSize(static_cast<sf::Vector2f>(windowSize));
	mouseStartClick = true;
}

/*************
Sets the background texture
*/
void Menu::setBgTexture(std::string path) {
	if (!bgTexture.loadFromFile(path)) { throw(std::string(path)); }
	background.setTexture(&bgTexture);
}

/*************
Sets the click sound
*/
void Menu::setClickSound(std::string path) {
	if (!clickBuffer.loadFromFile(path)) { throw(std::string(path)); }

	click.setBuffer(clickBuffer);
	click.setVolume(15.0f);
}

/*************
Checks if the mouse
 is over a button
*/
bool Menu::isMouseOver(sf::Vector2f mousePos, const sf::RectangleShape &button) {
	if (mousePos.x > button.getPosition().x && mousePos.y > button.getPosition().y
	    && mousePos.x < (button.getPosition().x + button.getSize().x)
	    && mousePos.y < (button.getPosition().y + button.getSize().y)) {
		return true;
	}
	return false;
}

/*************
Toggles the mute SFX.
*/
void Menu::toggleMuteSfx() {
	if (muteSfx) {
		muteSfx = false;
	} else {
		muteSfx = true;
	}
}

bool Menu::handleButton(sf::RectangleShape &button,
  const sf::Texture &buttonTexture,
  const sf::Texture &buttonInvTexture,
  const sf::Vector2f &mousePos) {
	bool isClicked = false;

	if (isMouseOver(mousePos, button)) {
		/*********************************
		When mouse is hovering over
		 the button:
		*********************************/
		button.setOutlineColor(sf::Color::White);
		button.setTexture(&buttonInvTexture);

		/*********************************
		When mouse clicks the button:
		*********************************/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseStartClick) {
			if (!muteSfx) click.play();
			mouseStartClick = false;
		} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseStartClick) {
			isClicked = true;
			button.setOutlineColor(sf::Color::Transparent);
			button.setTexture(&buttonTexture);
			mouseStartClick = true;
		}

		/*********************************
		When mouse leaves the button:
		*********************************/
	} else if (button.getOutlineColor() != sf::Color::Transparent) {
		button.setOutlineColor(sf::Color::Transparent);
	} else if (button.getTexture() != &buttonTexture) {
		button.setTexture(&buttonTexture);
	}

	return isClicked;
}

int Menu::run() { return 0; }

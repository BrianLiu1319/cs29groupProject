#include "SettingsMenu.hpp"

/*********************************
 Draws the settings menu.
 *********************************/
void SettingsMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(creditsButton);
	target.draw(howtoButton);
	target.draw(backButton);
	target.draw(sfxButton);
	target.draw(musicButton);
	target.draw(currDifficulty);
	target.draw(text);
	if (currDifficultyLevel < numOfDifficulty - 1) target.draw(nextButton);
	if (currDifficultyLevel > 0) target.draw(prevButton);
}

/*********************************
Constructor.
 Sets up the credits, how to play,
 sfx, music, and back button according
 to the window size.
*********************************/
SettingsMenu::SettingsMenu(sf::Vector2f windowSize) : Menu(windowSize), currDifficultyLevel(0) {
	// Calculate Button sizes and positions
	sf::Vector2f buttonSize(windowSize.x / 1920.0f * 600.0f, windowSize.y / 1080.0f * 135.0f);
	sf::Vector2f centerButtonPos(windowSize.x / 2.0f - buttonSize.x / 2,
	  windowSize.y / 2.0f - buttonSize.y / 2 + buttonSize.y);

	// Set Textures
	try {
		setBgTexture(menuBackgroundTexturePath);
		setCreditsTexture(creditsButtonTexturePath, creditsButtonTextureInvPath);
		setHowtoTexture(howtoButtonTexturePath, howtoButtonTextureInvPath);
		setBackTexture(backButtonTexturePath, backButtonTextureInvPath);
		setSfxTexture(sfxButtonPath, sfxMuteButtonPath, sfxButtonInvPath, sfxMuteButtonInvPath);
		setMusicTexture(musicButtonPath,
		  musicMuteButtonPath,
		  musicButtonInvPath,
		  musicMuteButtonInvPath);
		setClickSound(clickSFXPath01);
		setDifficultyTextures(difficultyPath);
		setNextTexture(nextButtonPath, nextButtonInvPath);
		setPrevTexture(prevButtonPath, prevButtonInvPath);
		setFont(fontPath);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: SettingsMenu" << std::endl;
		exit(1);
	}

	// Set Buttons
	creditsButton.setSize(buttonSize);
	creditsButton.setPosition(
	  sf::Vector2f(centerButtonPos.x, centerButtonPos.y + buttonSize.y * 1.25f));
	creditsButton.setOutlineThickness(buttonSize.y / 20.0f);
	howtoButton.setSize(buttonSize);
	howtoButton.setPosition(centerButtonPos);
	howtoButton.setOutlineThickness(buttonSize.y / 20.0f);
	musicButton.setSize(sf::Vector2f(buttonSize.x / 2.2f, buttonSize.y));
	// musicButton.setPosition(windowSize.x/2 - musicButton.getSize().x * 1.1f, centerButtonPos.y -
	// musicButton.getSize().x * 1.4f);
	musicButton.setPosition(centerButtonPos.x, centerButtonPos.y - buttonSize.y * 1.25f);
	musicButton.setOutlineThickness(buttonSize.y / 20.0f);
	sfxButton.setSize(sf::Vector2f(buttonSize.x / 2.2f, buttonSize.y));
	sfxButton.setPosition(windowSize.x / 2 + buttonSize.x * 0.05f,
	  centerButtonPos.y - buttonSize.y * 1.25f);
	sfxButton.setOutlineThickness(buttonSize.y / 20.0f);
	backButton.setSize(sf::Vector2f(buttonSize.y, buttonSize.y));
	backButton.setPosition(windowSize.x / 1920.0f * 20.0f, windowSize.x / 1920.0f * 20.0f);
	backButton.setOutlineThickness(buttonSize.y / 20.0f);
	currDifficulty.setSize(buttonSize);
	currDifficulty.setPosition(centerButtonPos.x, centerButtonPos.y - buttonSize.y * 2.6f);
	nextButton.setSize(sf::Vector2f(buttonSize.y / 3.0f, buttonSize.y));
	nextButton.setPosition(windowSize.x / 2 + buttonSize.y * 1.5f,
	  centerButtonPos.y - buttonSize.y * 2.6f);
	nextButton.setOutlineThickness(buttonSize.y / 20.0f);
	prevButton.setSize(sf::Vector2f(buttonSize.y / 3.0f, buttonSize.y));
	prevButton.setPosition(windowSize.x / 2 - buttonSize.y * 1.5f - prevButton.getSize().x,
	  centerButtonPos.y - buttonSize.y * 2.6f);
	prevButton.setOutlineThickness(buttonSize.y / 20.0f);

	// Set text
	text.setCharacterSize(static_cast<unsigned int>(windowSize.y / 25));
	text.setFillColor(sf::Color(107, 16, 16));
	text.setPosition(currDifficulty.getPosition().x + text.getCharacterSize() * 3.3f,
	  currDifficulty.getPosition().y - buttonSize.y / 3.0f);
	text.setString("Set Difficulty:");
}

/*********************************
Sets the texture and inversed
 texture of the credits button.
*********************************/
void SettingsMenu::setCreditsTexture(std::string path, std::string pathInv) {
	if (!creditsTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!creditsTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }

	creditsButton.setTexture(&creditsTexture);
}

/*********************************
Sets the texture and inversed
 texture of the how to play button.
*********************************/
void SettingsMenu::setHowtoTexture(std::string path, std::string pathInv) {
	if (!howtoTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!howtoTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }

	howtoButton.setTexture(&howtoTexture);
}

/*********************************
Sets the texture and mute
 texture of the sfx button.
*********************************/
void SettingsMenu::setSfxTexture(std::string path,
  std::string pathInv,
  std::string pathMute,
  std::string pathMuteInv) {
	if (!sfxTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!sfxMuteTexture.loadFromFile(pathInv)) { throw(std::string(pathInv)); }
	if (!sfxTextureInv.loadFromFile(pathMute)) { throw(std::string(pathMute)); }
	if (!sfxMuteTextureInv.loadFromFile(pathMuteInv)) { throw(std::string(pathMuteInv)); }

	sfxButton.setTexture(&sfxTexture);
}

/*********************************
Sets the texture and mute
 texture of the music button.
*********************************/
void SettingsMenu::setMusicTexture(std::string path,
  std::string pathInv,
  std::string pathMute,
  std::string pathMuteInv) {
	if (!musicTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!musicMuteTexture.loadFromFile(pathInv)) { throw(std::string(pathInv)); }
	if (!musicTextureInv.loadFromFile(pathMute)) { throw(std::string(pathMute)); }
	if (!musicMuteTextureInv.loadFromFile(pathMuteInv)) { throw(std::string(pathMuteInv)); }

	musicButton.setTexture(&musicTexture);
}

/*********************************
Sets the texture and inverse
 texture of the back button.
*********************************/
void SettingsMenu::setBackTexture(std::string path, std::string pathInv) {
	if (!backTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!backTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }

	backButton.setTexture(&backTexture);
}

/*********************************
Sets the textures for the difficulty
 levels.
*********************************/
void SettingsMenu::setDifficultyTextures(std::string path) {
	for (int i = 0; i < numOfDifficulty; i++) {
		if (!difficultyLevelTextures[i].loadFromFile(path + std::to_string(i + 1) + ".png")) {
			throw(std::string(path));
		}
	}

	currDifficulty.setTexture(&difficultyLevelTextures[0]);
}

/*********************************
Sets the texture and inverse
 texture of the next button.
*********************************/
void SettingsMenu::setNextTexture(std::string path, std::string pathInv) {
	if (!nextTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!nextTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }

	nextButton.setTexture(&nextTexture);
}

/*********************************
Sets the texture and inverse
 texture of the prev button.
*********************************/
void SettingsMenu::setPrevTexture(std::string path, std::string pathInv) {
	if (!prevTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!prevTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }

	prevButton.setTexture(&prevTexture);
}

/*********************************
Runs the settings menu.
*********************************/
int SettingsMenu::run(sf::Vector2f mousePos) {
	/***
	 states:
	 0 - Settings Menu
	 1 - Back to Main Menu
	 2 - Credits
	 3 - How to Play
	 4 - Toggle Music Mute and stay in Settings Menu
	 5 - Toggle SFX Mute and stay in Settings Menu
	 6 - Increase Difficulty
	 7 - Decrease Difficulty
	 */
	int state = 0;

	// Handle actions on the back button.
	if (handleButton(backButton, backTexture, backTextureInv, mousePos)) { state = 1; }

	// Handle actions on the credits button
	if (handleButton(creditsButton, creditsTexture, creditsTextureInv, mousePos)) { state = 2; }

	// Handle actions on the how to play button.
	if (handleButton(howtoButton, howtoTexture, howtoTextureInv, mousePos)) { state = 3; }

	// Handle actions on the music button.
	if (handleSoundButton(musicButton,
	      musicTexture,
	      musicTextureInv,
	      musicMuteTexture,
	      musicMuteTextureInv,
	      mousePos)) {
		state = 4;
	}

	// Handle actions on the sfx button.
	if (handleSoundButton(sfxButton,
	      sfxTexture,
	      sfxTextureInv,
	      sfxMuteTexture,
	      sfxMuteTextureInv,
	      mousePos)) {
		state = 5;
	}

	// Handle actions on the next and prev buttons.
	if (currDifficultyLevel < numOfDifficulty - 1
	    && handleButton(nextButton, nextTexture, nextTextureInv, mousePos)) {
		currDifficultyLevel++;
		currDifficulty.setTexture(&difficultyLevelTextures[currDifficultyLevel]);
		state = 6;
	}

	if (currDifficultyLevel > 0
	    && handleButton(prevButton, prevTexture, prevTextureInv, mousePos)) {
		currDifficultyLevel--;
		currDifficulty.setTexture(&difficultyLevelTextures[currDifficultyLevel]);
		state = 7;
	}

	return state;
}

/*********************************
Handle actions on a sound button.
*********************************/
bool SettingsMenu::handleSoundButton(sf::RectangleShape &button,
  const sf::Texture &buttonTexture,
  const sf::Texture &buttonInvTexture,
  const sf::Texture &buttonMuteTexture,
  const sf::Texture &buttonMuteInvTexture,
  const sf::Vector2f &mousePos) {
	bool isClicked = false;

	if (isMouseOver(mousePos, button)) {
		/*********************************
		When mouse is hovering over
		 the button:
		*********************************/
		button.setOutlineColor(sf::Color::White);
		if (button.getTexture() == &buttonTexture) {
			button.setTexture(&buttonInvTexture);
		} else if (button.getTexture() == &buttonMuteTexture) {
			button.setTexture(&buttonMuteInvTexture);
		}

		/*********************************
		When mouse clicks the button:
		*********************************/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseStartClick) {
			if (!muteSfx) click.play();
			mouseStartClick = false;
		} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseStartClick) {
			isClicked = true;
			if (button.getTexture() == &buttonTexture || button.getTexture() == &buttonInvTexture) {
				button.setTexture(&buttonMuteTexture);
			} else {
				button.setTexture(&buttonTexture);
			}
			button.setOutlineColor(sf::Color::Transparent);
			mouseStartClick = true;
		}

		/*********************************
		When mouse leaves the button:
		*********************************/
	} else if (button.getOutlineColor() != sf::Color::Transparent) {
		button.setOutlineColor(sf::Color::Transparent);
	} else if (button.getTexture() != &buttonTexture || button.getTexture() != &buttonMuteTexture) {
		if (button.getTexture() == &buttonInvTexture) {
			button.setTexture(&buttonTexture);
		} else if (button.getTexture() == &buttonMuteInvTexture) {
			button.setTexture(&buttonMuteTexture);
		}
	}

	return isClicked;
}

/*********************************
Sets the font for the text.
 Throws the path of file if not found.
*********************************/
void SettingsMenu::setFont(std::string path) {
	if (!textFont.loadFromFile(path.c_str())) { throw(std::string(path)); }
	text.setFont(textFont);
}

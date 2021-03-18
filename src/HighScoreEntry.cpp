#include "HighScoreEntry.hpp"

/*********************************
 Draws the high scores panel.
 *********************************/
void HighScoreEntry::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(confirmButton);
	target.draw(textBox);
	target.draw(inputText);
	if (textTyped.length() == 0) { target.draw(maxLengthText); }
	if (cursorOn) { target.draw(cursor); }
}

/*********************************
Constructor.
 Sets up everything according to the
 window size.
*********************************/
HighScoreEntry::HighScoreEntry(sf::Vector2f windowSize) : Menu(windowSize), defaultCursorPos(0, 0) {
	sf::Vector2f buttonSize(windowSize.x / 1920.0f * 600.0f, windowSize.y / 1080.0f * 135.0f);
	sf::Vector2f centerButtonPos(windowSize.x / 2.0f - buttonSize.x / 2,
	  windowSize.y / 2.0f - buttonSize.y / 2);

	// Set Textures
	try {
		setFont(fontPath);
		setBgTexture(bgPath);
		// background.setFillColor(sf::Color::Yellow);
		setConfirmButtonTexture(confirmButtonPath, confirmButtonInvPath);
		setClickSound(clickSFXPath01);

		setCongratsSfx();

	} catch (const std::string &fileName) {
		std::cerr << "Unable to open file " << fileName << std::endl;
		std::cerr << "Location: HighScoreEntry" << std::endl;
		exit(1);
	}

	// Set Size, Position, Color, etc.
	textBox.setFillColor(sf::Color::White);
	confirmButton.setSize(sf::Vector2f(buttonSize.x, buttonSize.y));
	confirmButton.setPosition(centerButtonPos.x, centerButtonPos.y + buttonSize.y * 1.8f);
	confirmButton.setOutlineThickness(buttonSize.y / 20.0f);
	textBox.setSize(sf::Vector2f(buttonSize.x, buttonSize.y));
	textBox.setPosition(centerButtonPos.x, centerButtonPos.y + buttonSize.y * 0.5f);
	maxLengthText.setCharacterSize(static_cast<unsigned int>(windowSize.y / 18));
	maxLengthText.setFillColor(sf::Color(220, 220, 220));
	maxLengthText.setString("max. 16 chars");
	maxLengthText.setPosition(textBox.getPosition().x + maxLengthText.getCharacterSize() * 0.5f,
	  textBox.getPosition().y + maxLengthText.getCharacterSize() * 0.5f);
	inputText.setCharacterSize(static_cast<unsigned int>(windowSize.y / 18));
	inputText.setFillColor(sf::Color(107, 16, 16));
	inputText.setPosition(textBox.getPosition().x + inputText.getCharacterSize() * 0.5f,
	  textBox.getPosition().y + inputText.getCharacterSize() * 0.5f);
	cursor.setFillColor(sf::Color(107, 16, 16));
	cursor.setSize(sf::Vector2f(windowSize.x / 500.0f, windowSize.y / 14.0f));
	defaultCursorPos += sf::Vector2f(textBox.getPosition().x + inputText.getCharacterSize() * 0.5f,
	  textBox.getPosition().y + inputText.getCharacterSize() * 0.5f);
	cursor.setPosition(defaultCursorPos);

	totalTime = 0.0f;
	switchTime = 0.5f;
	cursorOn = false;
}

/*********************************
Sets the font for the text.
 Throws the path of file if not found.
*********************************/
void HighScoreEntry::setFont(const std::string& path) {
	if (!inputTextFont.loadFromFile(path)) { throw(std::string(path)); }
	inputText.setFont(inputTextFont);
	maxLengthText.setFont(inputTextFont);
}

/*********************************
Sets the texture for the confirm button.
 Throws the path of file if not found.
*********************************/
void HighScoreEntry::setConfirmButtonTexture(const std::string& path, const std::string& pathInv) {
	if (!confirmButtonTexture.loadFromFile(path)) { throw(std::string(path)); }
	if (!confirmButtonTextureInv.loadFromFile(pathInv)) { throw(std::string(pathInv)); }

	confirmButton.setTexture(&confirmButtonTexture);
}

/*********************************
Runs the High Score Entry box.
 Returns true if the user has clicked "Confirm".
 Returns false otherwise.
 Updates the blinking cursor based on the
 delta time.
*********************************/
int HighScoreEntry::run(sf::Vector2f mousePos, float deltaTime) {
	/***
	confirmed:
	0 - High Score Entry
	1 - Back to Main Menu
	*/
	int confirmed = 0;

	if (!muteSfx && !congratsHasPlayed && congrats.getStatus() != sf::Sound::Playing) {
		congratsHasPlayed = true;
		congrats.play();
	}

	// Update cursor for text input.
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		if (cursorOn) {
			cursorOn = false;
		} else {
			cursorOn = true;
		}
	}

	// Handle actions on the confirm button.
	if (handleButton(confirmButton, confirmButtonTexture, confirmButtonTextureInv, mousePos)) {
		confirmed = 1;

		score.setName(textTyped);
		score.setDate(time(nullptr));

		textTyped.erase(textTyped.begin(), textTyped.end());
		inputText.setString(textTyped);
		cursor.setPosition(defaultCursorPos);

		congratsHasPlayed = false;
		congrats.stop();
	}

	return confirmed;
}

/*********************************
Enters a character into the input text.
 Maximum length for the text is 16
 (for output formatting purposes).
 Anything beyond that is deleted.
 Also updates the position of the
 cursor to the end of the text.
*********************************/
void HighScoreEntry::enterText(char c) {
	if (c == 8) {
		if (textTyped.length() != 0) {
			textTyped.pop_back();
			cursor.setPosition(cursor.getPosition().x - inputText.getCharacterSize(),
			  cursor.getPosition().y);
		}
	} else {
		textTyped += c;
		cursor.setPosition(cursor.getPosition().x + inputText.getCharacterSize(),
		  cursor.getPosition().y);
	}

	while (textTyped.length() > 16) { textTyped.pop_back(); }

	inputText.setString(textTyped);

	float width = inputText.getLocalBounds().width;
	cursor.setPosition(defaultCursorPos.x + width, defaultCursorPos.y);
}

void HighScoreEntry::setCongratsSfx() {
	if (!congratsSoundBuffer.loadFromFile(congratsPath)) { throw(std::string(congratsPath)); }

	congrats.setBuffer(congratsSoundBuffer);
	congrats.setVolume(15.0f);
}

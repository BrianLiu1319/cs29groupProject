#include "ValueDisplay.hpp"

void ValueDisplay::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(moneyDisplay);
	target.draw(moneyText);
	target.draw(scoreDisplay);
	target.draw(scoreText);
	if (currentMode == MODE::countdown)
		target.draw(waveCountdown);
	else
		target.draw(currentWave);
}

ValueDisplay::ValueDisplay(sf::Vector2f windowSize) {
	currentMode = MODE::countdown;

	sf::Vector2f size(windowSize.x / 6.0f, windowSize.y / 10.0f);
	sf::Vector2f pos(windowSize.x - size.x * 1.2f, size.y);
	sf::Vector2f posText(windowSize.x - size.x * 0.8f, size.y * 1.2f);

	// load textures and font
	try {
		if (!scoreDisplayTexture.loadFromFile(scoreDisplayPath)) { throw scoreDisplayPath; }
		scoreDisplay.setTexture(&scoreDisplayTexture);
		if (!moneyDisplayTexture.loadFromFile(moneyDisplayPath)) { throw moneyDisplayPath; }
		moneyDisplay.setTexture(&moneyDisplayTexture);
		if (!font.loadFromFile(fontFile)) { throw fontFile; }
		moneyText.setFont(font);
		scoreText.setFont(font);
		currentWave.setFont(font);
		waveCountdown.setFont(font);

	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: ValueDisplay" << std::endl;
		exit(1);
	}

	// set up
	moneyDisplay.setSize(size);
	scoreDisplay.setSize(size);
	moneyDisplay.setPosition(pos);
	scoreDisplay.setPosition(pos.x, pos.y + size.y * 1.2f);
	moneyText.setCharacterSize(static_cast<unsigned int>(windowSize.y / 22));
	moneyText.setFillColor(sf::Color(242, 218, 0));
	moneyText.setPosition(posText);
	moneyText.setString("0");
	scoreText.setCharacterSize(static_cast<unsigned int>(windowSize.y / 22));
	scoreText.setFillColor(sf::Color(242, 218, 0));
	scoreText.setPosition(posText.x, posText.y + size.y * 1.2f);
	scoreText.setString("0");
	currentWave.setString("Wave: 0");
	waveCountdown.setString("Starting in... 0");
	currentWave.setCharacterSize(static_cast<unsigned int>(windowSize.y / 24));
	waveCountdown.setCharacterSize(static_cast<unsigned int>(windowSize.y / 24));
	currentWave.setFillColor(sf::Color(107, 16, 16));
	waveCountdown.setFillColor(sf::Color(107, 16, 16));
	currentWave.setPosition(pos.x, posText.y + size.y * 2.4f);
	waveCountdown.setPosition(pos.x - size.x * 0.2f, posText.y + size.y * 2.4f);
}

void ValueDisplay::updateScore(int s) { scoreText.setString(std::to_string(s)); }

void ValueDisplay::updateMoney(int m) { moneyText.setString(std::to_string(m)); }

void ValueDisplay::setCountdownMode() { currentMode = MODE::countdown; }

void ValueDisplay::setWaveMode() { currentMode = MODE::wave; }

void ValueDisplay::updateCountdown(int c) {
	waveCountdown.setString("Starting in... " + std::to_string(timeBeforeStart - c));
}

void ValueDisplay::updateWave(int w) { currentWave.setString("Wave: " + std::to_string(w)); }

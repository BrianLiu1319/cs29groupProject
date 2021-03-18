#include "Animation.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "HighScoreEntry.hpp"
#include "StartMenu.hpp"

using namespace std;

int main() {
	/*********************************
	Create a RenderWindow and Game
	*********************************/
	sf::RenderWindow window(sf::VideoMode(1280, 720),
	  "Dogs vs Cats",
	  sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
	Game dogsVsCats(static_cast<sf::Vector2f>(window.getSize()));

	/*********************************
	Set up necessary stuff
	*********************************/
	StartMenu startMenu(static_cast<sf::Vector2f>(window.getSize()));
	HighScoreEntry highScoreEntryBox(static_cast<sf::Vector2f>(window.getSize()));
	Score temp;
	int state;
	GameOver gameOverScreen(static_cast<sf::Vector2f>(window.getSize()));

	/*********************************
	Set up the clock
	*********************************/
	float deltaTime;
	sf::Clock clock;

	/*********************************
	 The current state of the game.
	 - menu
	 - play game
	 - enter high score
	 - game over
	 *********************************/
	enum class states { menu, playGame, gameOver, enterHighScore };
	states gameState = states::menu;

	/*********************************
	Start the game
	*********************************/
	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();

		Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			if (gameState == states::enterHighScore && event.type == sf::Event::TextEntered) {
				if (event.text.unicode == 8 || (event.text.unicode > 31 && event.text.unicode < 127)) {
					highScoreEntryBox.enterText(static_cast<char>(event.text.unicode));
				}
			}
		}

		window.clear();

		switch (gameState) {
			case states::menu:
				window.draw(startMenu);
				state = startMenu.run(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

				switch (state) {
					case 0: gameState = states::playGame; break;
					// case 1:
					case 2:
						// Mute/unmute Music
						dogsVsCats.toggleMuteMusic();
						break;
					case 3:
						// Mute/unmute SFX
						highScoreEntryBox.toggleMuteSfx();
						dogsVsCats.toggleMuteSfx();
						gameOverScreen.toggleMuteSfx();
						break;
					case 4:
						// difficulty++;
						dogsVsCats.increaseDifficulty();
						break;
					case 5:
						// difficulty--;
						dogsVsCats.decreaseDifficulty();
						break;
					default:break;
				}

				break;

			case states::playGame:

				dogsVsCats.run(window);
				gameState = states::gameOver;
				temp.setScore(dogsVsCats.getScore());
				highScoreEntryBox.setScoreValue(dogsVsCats.getScore());

				break;

			case states::gameOver:
				gameOverScreen.setScore(dogsVsCats.getScore());
				window.draw(gameOverScreen);
				if (gameOverScreen.run(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
					if (startMenu.isHighScore(temp)) {
						gameState = states::enterHighScore;
						highScoreEntryBox.setScoreValue(dogsVsCats.getScore());
					} else {
						gameState = states::menu;
					}
				}

				clock.restart().asSeconds();

				break;

			case states::enterHighScore:

				window.draw(highScoreEntryBox);
				if (highScoreEntryBox.run(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)),
				      deltaTime)) {
					gameState = states::menu;
					temp = highScoreEntryBox.getScore();
					startMenu.updateScores(temp);
				}

				break;
		}
		window.display();
	}
}

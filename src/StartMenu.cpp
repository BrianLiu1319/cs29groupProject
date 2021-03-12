#include "StartMenu.hpp"

/*********************************
Draws the menu screen.
*********************************/
void StartMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	switch (gameState) {
		case mainM: target.draw(mainMenu); break;
		case settingM: target.draw(settings); break;
		case howToPlayM: target.draw(howToPlay); break;
		case creditsM: target.draw(credits); break;
	}
}

/*********************************
Constructor.
 Sets up all menus according to
 window size. Sets the game state
 to the default (main menu).
*********************************/
StartMenu::StartMenu(sf::Vector2f windowSize) :
    mainMenu(windowSize), settings(windowSize), credits(windowSize),
    howToPlay(windowSize) {
	gameState = mainM;
	status = 0;
	try {
		setBgSound(menuBGMusicPath);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: StartMenu" << std::endl;
		exit(1);
	}
}

/*********************************
Sets the background music.
*********************************/
void StartMenu::setBgSound(std::string path) {
	if (!bgMusicBuffer.loadFromFile(path)) { throw(std::string(path)); }

	bgMusic.setBuffer(bgMusicBuffer);
	bgMusic.setLoop(true);
	bgMusic.setVolume(15.0f);
}

/*********************************
Runs the menu.
 Returns 0 to run the main game.
 Returns 1 to stay on the menu.
 Returns 2 to toggle mute music and stay on the menu.
 Returns 3 to toggle mute sfx and stay on the menu.
*********************************/
int StartMenu::run(sf::Vector2f mousePos) {
	int state = 1;

	if (!muteMusic && bgMusic.getStatus() != sf::Sound::Playing) { bgMusic.play(); }
	if (muteMusic && bgMusic.getStatus() != sf::Sound::Stopped) { bgMusic.stop(); }

	switch (gameState) {
		case mainM: {
			status = mainMenu.run(mousePos);
			switch (status) {
					// case 0: gameState = mainMenu; break;
				case 1: state = 0; break;
				case 2: gameState = settingM; break;
			}

			break;
		}

		case settingM:
			status = settings.run(mousePos);

			switch (status) {
					// case 0: gameState = settingMenu; break;
				case 1: gameState = mainM; break;
				case 2: gameState = creditsM; break;
				case 3: gameState = howToPlayM; break;
				case 4:
					if (muteMusic) {
						muteMusic = false;
					} else {
						muteMusic = true;
					}
					state = 2;
					break;
				case 5:
					settings.toggleMuteSfx();
					mainMenu.toggleMuteSfx();
					credits.toggleMuteSfx();
					howToPlay.toggleMuteSfx();
					state = 3;
					break;
			}

			break;

		case howToPlayM:
			status = howToPlay.run(mousePos);
			switch (status) {
					// case 0: gameState = settingMenu; break;
				case 1: gameState = settingM; break;
			}
			break;

		case creditsM:

			status = credits.run(mousePos);
			switch (status) {
					// case 0: gameState = settingMenu; break;
				case 1: gameState = settingM; break;
			}
			break;
	}

	if (state == 0) { bgMusic.stop(); }

	return state;
}

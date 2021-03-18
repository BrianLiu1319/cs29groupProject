#include "StartMenu.hpp"

/*********************************
Draws the menu screen.
*********************************/
void StartMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	switch (gameState) {
		case startStates::mainM: target.draw(mainMenu); break;
		case startStates::settingM: target.draw(settings); break;
		case startStates::howToPlayM: target.draw(howToPlay); break;
		case startStates::creditsM: target.draw(credits); break;
	}
}

/*********************************
Constructor.
 Sets up all menus according to
 window size. Sets the game state
 to the default (main menu).
*********************************/
StartMenu::StartMenu(sf::Vector2f windowSize) :
    mainMenu(windowSize), settings(windowSize), credits(windowSize), howToPlay(windowSize) {
	gameState = startStates::mainM;
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
	if (!bgMusic.openFromFile(path)) { throw(std::string(path)); }

	bgMusic.setLoop(true);
	bgMusic.setVolume(15.0f);
}

/*********************************
Runs the menu.
 Returns:
 0 - run the main game.
 1 - stay on the menu.
 2 - toggle mute music and stay on the menu.
 3 - toggle mute sfx and stay on the menu.
 4 - increase difficulty and stay on the menu
 5 - decrease difficulty and stay on the menu
*********************************/
int StartMenu::run(sf::Vector2f mousePos) {
	int state = 1;

	if (!muteMusic && bgMusic.getStatus() != sf::Sound::Playing) { bgMusic.play(); }
	if (muteMusic && bgMusic.getStatus() != sf::Sound::Stopped) { bgMusic.stop(); }

	switch (gameState) {
		case startStates::mainM: {
			status = mainMenu.run(mousePos);
			switch (status) {
				case 1: state = 0; break;
				case 2: gameState = startStates::settingM; break;
					default:break;
			}

			break;
		}

		case startStates::settingM:
			status = settings.run(mousePos);

			switch (status) {
				case 1: gameState = startStates::mainM; break;
				case 2: gameState = startStates::creditsM; break;
				case 3: gameState = startStates::howToPlayM; break;
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
				case 6: state = 4; break;
				case 7: state = 5; break;
					default:break;
			}

			break;

		case startStates::howToPlayM:
			status = howToPlay.run(mousePos);
			switch (status) {
				case 1: gameState = startStates::settingM; break;
					default:break;
			}
			break;

		case startStates::creditsM:

			status = credits.run(mousePos);
			switch (status) {
				case 1: gameState = startStates::settingM; break;
					default:break;
			}
			break;
	}

	if (state == 0) { bgMusic.stop(); }

	return state;
}

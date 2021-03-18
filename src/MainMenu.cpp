#include "MainMenu.hpp"

/*********************************
 Draws the main menu.
 *********************************/
void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(background);
  target.draw(playButton);
  target.draw(settingButton);
  target.draw(highScoresPanel);
}

/*********************************
Constructor.
 Sets up the play, exit, and
 settings button according to
 the window size.
*********************************/
MainMenu::MainMenu(sf::Vector2f windowSize)
    : Menu(windowSize), highScoresPanel(windowSize) {

  // Calculate Button sizes and positions
  sf::Vector2f buttonSize(windowSize.x / 1920.0f * 600.0f,
                          windowSize.y / 1080.0f * 135.0f);
  sf::Vector2f centerButtonPos(
      windowSize.x / 1920.0f * 1350.0f - buttonSize.x / 2,
      windowSize.y / 1080.0f * 700.0f - buttonSize.y / 2);

  // Set Buttons
  playButton.setSize(buttonSize);
  playButton.setPosition(centerButtonPos);
  playButton.setOutlineThickness(buttonSize.y / 20.0f);
  settingButton.setSize(buttonSize);
  settingButton.setPosition(sf::Vector2f(
      centerButtonPos.x, centerButtonPos.y + buttonSize.y * 1.25f));
  settingButton.setOutlineThickness(buttonSize.y / 20.0f);

  // Set Textures
  try {
    setBgTexture(menuBackgroundTexturePath);
    setPlayTexture(playButtonTexturePath, playButtonTextureInvPath);
    setSettingTexture(settingButtonTexturePath, settingButtonTextureInvPath);
    setClickSound(clickSFXPath01);
  } catch (const std::string &fileName) {
    std::cerr << "Unable to open the file " << fileName << std::endl;
    std::cerr << "Location: MainMenu" << std::endl;
    exit(1);
  }
}

/*********************************
Sets the texture and inversed
 texture of the play button.
*********************************/
void MainMenu::setPlayTexture(std::string path, std::string pathInv) {
  if (!playTexture.loadFromFile(path)) {
    throw(std::string(path));
  }
  if (!playTextureInv.loadFromFile(pathInv)) {
    throw(std::string(pathInv));
  }

  playButton.setTexture(&playTexture);
}

/*********************************
Sets the texture and inversed
 texture of the settings button.
*********************************/
void MainMenu::setSettingTexture(std::string path, std::string pathInv) {
  if (!settingTexture.loadFromFile(path)) {
    throw(std::string(path));
  }
  if (!settingTextureInv.loadFromFile(pathInv)) {
    throw(std::string(pathInv));
  }

  settingButton.setTexture(&settingTexture);
}

/*********************************
Runs the main menu.
*********************************/
int MainMenu::run(sf::Vector2f mousePos) {

  /***
   states:
   0 - Main Menu
   1 - Play Game
   2 - Settings Menu
   */
  int state = 0;

  // Handle actions on the play button.
  if (handleButton(playButton, playTexture, playTextureInv, mousePos)) {
    state = 1;
  }

  // Handle actions on the settings button.
  if (handleButton(settingButton, settingTexture, settingTextureInv,
                   mousePos)) {
    state = 2;
  }

  return state;
}

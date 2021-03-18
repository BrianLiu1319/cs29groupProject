#pragma once

#include "Credits.hpp"
#include "FolderPath.hpp"
#include "HowToPlay.hpp"
#include "MainMenu.hpp"
#include "Score.hpp"
#include "SettingsMenu.hpp"

class StartMenu : public sf::Drawable {
  // NOTE: Go to FolderPath.hpp to change the Folder Path.
private:
  enum class startStates { mainM, settingM, howToPlayM, creditsM };
  startStates gameState;

  const std::string menuBGMusicPath = assetFolder + "Wii Music.wav";

  int status;
  bool muteMusic = false;

  MainMenu mainMenu;
  SettingsMenu settings;
  Credits credits;
  HowToPlay howToPlay;
  sf::Music bgMusic;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
  StartMenu(sf::Vector2f windowSize);
  int run(sf::Vector2f mousePos);
  void setBgSound(std::string path);
  void updateScores(const Score &s) { mainMenu.updateScores(s); }
  bool isHighScore(const Score &s) const { return mainMenu.isHighScore(s); };
};

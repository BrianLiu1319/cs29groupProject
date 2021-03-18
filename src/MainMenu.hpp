#pragma once

#include "HighScoresPanel.hpp"
#include "Menu.hpp"
#include "Score.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class MainMenu : public Menu {
  // NOTE: Go to FolderPath.hpp to change the Folder Path.
private:
  const std::string menuBackgroundTexturePath =
      assetFolder + "main menu bg-01.png";
  const std::string playButtonTexturePath = assetFolder + "play button.png";
  const std::string playButtonTextureInvPath =
      assetFolder + "play button inverted.png";
  const std::string settingButtonTexturePath =
      assetFolder + "setting button.png";
  const std::string settingButtonTextureInvPath =
      assetFolder + "setting button inverted.png";
  const std::string clickSFXPath01 = assetFolder + "click02.wav";
  const std::string highScoresTexturePath = assetFolder + "high scores.png";

  sf::Texture playTexture, settingTexture, playTextureInv, settingTextureInv;
  sf::RectangleShape playButton, settingButton;
  HighScoresPanel highScoresPanel;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
  MainMenu(sf::Vector2f windowSize);
  void setPlayTexture(std::string path, std::string pathInv);
  void setSettingTexture(std::string path, std::string pathInv);
  int run(sf::Vector2f mousePos);
  void updateScores(const Score &s) { highScoresPanel.update(s); }
  bool isHighScore(const Score &s) const {
    return highScoresPanel.isHighScore(s);
  }
};

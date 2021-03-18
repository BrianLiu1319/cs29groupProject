#pragma once
#include "FolderPath.hpp"
#include "Menu.hpp"

class GameOver : public Menu {
  // NOTE: go to Folder.hpp to change the folder path
private:
  bool sfxHasPlayed = false;
  unsigned int score;

  const std::string confirmButtonPath = assetFolder + "confirm button.png";
  const std::string confirmButtonInvPath =
      assetFolder + "confirm button inverted.png";
  const std::string fontPath = assetFolder + "AnonymousPro-Regular.ttf";
  const std::string clickSFXPath01 = assetFolder + "click02.wav";
  const std::string clawPath = assetFolder + "claw mark.png";
  const std::string gameOverSoundPath = assetFolder + "game over.wav";

  sf::RectangleShape confirmButton, clawMark;
  sf::Texture confirmButtonTexture, confirmButtonTextureInv, clawMarkTexture;
  sf::Font textFont;
  sf::Text text;
  sf::SoundBuffer gameOverSoundBuffer;
  sf::Sound gameOverSound;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  void setText();
  void setGameOverSound();

public:
  GameOver(sf::Vector2f windowSize);
  int run(sf::Vector2f mousePos);
  void setConfirmButtonTexture(std::string path, std::string pathInv);
  void setFont(std::string path);
  void setScore(unsigned int s);
};

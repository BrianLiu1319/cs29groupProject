#pragma once

#include "FolderPath.hpp"
#include "Menu.hpp"
#include "Score.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class HighScoreEntry : public Menu {
    // NOTE: go to Folder.hpp to change the folder path
private:
  const std::string bgPath = assetFolder + "high score entry-01.png";
  const std::string confirmButtonPath = assetFolder + "confirm button.png";
  const std::string confirmButtonInvPath =
      assetFolder + "confirm button inverted.png";
  const std::string fontPath = assetFolder + "AnonymousPro-Regular.ttf";
  const std::string clickSFXPath01 = assetFolder + "click02.wav";
  const std::string congratsPath = assetFolder + "high score.wav";

  sf::RectangleShape textBox, confirmButton, cursor;
  sf::Texture confirmButtonTexture, confirmButtonTextureInv;
  sf::Font inputTextFont;
  sf::Text inputText, maxLengthText;
  sf::Vector2f defaultCursorPos;
  Score score;
  std::string textTyped;
  sf::SoundBuffer congratsSoundBuffer;
  sf::Sound congrats;

  float totalTime;
  float switchTime;
  bool cursorOn;
  bool congratsHasPlayed = false;

  void setCongratsSfx();
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
  HighScoreEntry(sf::Vector2f windowSize);
  void setConfirmButtonTexture(std::string path, std::string pathInv);
  void setFont(std::string path);
  int run(sf::Vector2f mousePos, float deltaTime);
  void enterText(char c);
  void setScoreValue(unsigned int s) { score.setScore(s); }
  Score getScore() const { return score; }
};


#pragma once

#include "FolderPath.hpp"
#include "Score.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iomanip>
#include <set>
#include <sstream>

class HighScoresPanel : public sf::Drawable {
  // NOTE: Go to FolderPath.hpp to change the Folder Path.
private:
  const std::string highScoreFilePath = assetFolder + "highScores.bin";
  const std::string panelTexturePath = assetFolder + "high scores.png";
  const std::string fontPath = assetFolder + "AnonymousPro-Regular.ttf";

  static const int maxScores = 10;

  std::multiset<Score, std::greater<Score>> scores;
  sf::RectangleShape panel;
  sf::Texture panelTexture;
  sf::Font textFont;
  sf::Text scoresText;

  void readHighScoresFile();
  void writeHighScoresFile();
  void updateScoresText();

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
  HighScoresPanel(sf::Vector2f windowSize);
  void update(const Score &s);
  void setPanelTexture(std::string path);
  void setFont(std::string path);
  bool isHighScore(const Score &s) const;
};

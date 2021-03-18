#pragma once


#include "FolderPath.hpp"
#include "Menu.hpp"

class Credits : public Menu {
    // NOTE: Go to FolderPath.hpp to change the Folder Path.
private:
  const std::string menuBackgroundTexturePath =
      assetFolder + "credits menu bg-01.png";
  const std::string backButtonPath = assetFolder + "back button.png";
  const std::string backButtonInvPath =
      assetFolder + "back button inverted.png";
  const std::string clickSFXPath01 = assetFolder + "click02.wav";

  sf::Texture backTexture, backTextureInv;
  sf::RectangleShape backButton;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
  Credits(sf::Vector2f windowSize);
  void setBackTexture(std::string path, std::string pathInv);
  int run(sf::Vector2f mousePos);
};



#pragma once

#include "Menu.hpp"

class Toolbar : public Menu {
    // NOTE: Go to Folder.h to change the Folder Path.
private:

  const std::string whistlePath = assetFolder + "whistle.png";
  const std::string whistlePathInv = assetFolder + "whistle inv.png";
  const std::string healthPath = assetFolder + "health.png";
  const std::string healthPathInv = assetFolder + "health inv.png";
  const std::string clickSFXPath01 = assetFolder + "click02.wav";

  int healthCost = 40;
  int whistleRefund = 20;
  bool mute = false;

  sf::Texture whistleTexture, whistleTextureInv, healthTexture,
      healthTextureInv;
  sf::RectangleShape whistleButton, healthButton;
  enum class SELECTION { none, whistle, health };
  SELECTION currentSelection = SELECTION::none;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  void setWhistleTexture();
  void setHealthTexture();
  bool handleButton(sf::RectangleShape &button,
                    const sf::Texture &buttonTexture,
                    const sf::Texture &buttonInvTexture,
                    const sf::Vector2f &mousePos);

public:
  Toolbar(sf::Vector2f windowSize);
  int run(sf::Vector2f mousePos);
  bool whistleSelected();
  bool healthSelected();
  void deselectAll();
  int getHealthCost() const { return healthCost; }
  int getWhistleRefund() const { return whistleRefund; }
};


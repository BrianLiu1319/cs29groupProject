#pragma once

#include "FolderPath.hpp"
#include "Menu.hpp"

#include <array>

class HowToPlay : public Menu {
	// NOTE: Go to FolderPath.hpp to change the Folder Path.
private:
	const std::string menuBackgroundTexturePath = assetFolder + "how to play bg-01.png";
	const std::string nextButtonPath = assetFolder + "next button.png";
	const std::string nextButtonInvPath = assetFolder + "next button inverted.png";
	const std::string prevButtonPath = assetFolder + "prev button.png";
	const std::string prevButtonInvPath = assetFolder + "prev button inverted.png";
	const std::string backButtonPath = assetFolder + "back button.png";
	const std::string backButtonInvPath = assetFolder + "back button inverted.png";
	const std::string clickSFXPath01 = assetFolder + "click02.wav";
	const std::string guidePagePath = assetFolder + "guide-";

	static const unsigned int maxPage = 12;
	unsigned page;

	sf::Texture nextTexture, prevTexture, backTexture, nextTextureInv, prevTextureInv,
	  backTextureInv;
	sf::RectangleShape nextButton, prevButton, backButton, guidePage;
	std::array<sf::Texture, maxPage> guidePageTexture;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	HowToPlay(sf::Vector2f windowSize);
	void setNextTexture(std::string path, std::string pathInv);
	void setPrevTexture(std::string path, std::string pathInv);
	void setBackTexture(std::string path, std::string pathInv);
	int run(sf::Vector2f mousePos);
};

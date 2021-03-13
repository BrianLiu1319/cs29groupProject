#ifndef HowToPlay_hpp
#define HowToPlay_hpp

#include "Menu.hpp"

#include <array>

class HowToPlay : public Menu {
private:
	// NOTE: Go to Menu.hpp to change the Folder Path.

	// File names
	const std::string menuBackgroundTexturePath = assetFolder + "how to play bg-01.png";
	const std::string nextButtonPath = assetFolder + "next button.png";
	const std::string nextButtonInvPath = assetFolder + "next button inverted.png";
	const std::string prevButtonPath = assetFolder + "prev button.png";
	const std::string prevButtonInvPath = assetFolder + "prev button inverted.png";
	const std::string backButtonPath = assetFolder + "back button.png";
	const std::string backButtonInvPath = assetFolder + "back button inverted.png";
	const std::string clickSFXPath01 = assetFolder + "click02.wav";
	const std::string guidePagePath = assetFolder + "guide-";


	sf::Texture nextTexture, prevTexture, backTexture, nextTextureInv, prevTextureInv,
	  backTextureInv;
	sf::RectangleShape nextButton, prevButton, backButton, guidePage;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	int page;
	static const int maxPage = 4;
	std::array<sf::Texture, maxPage> guidePageTexture;

public:
	HowToPlay(sf::Vector2f windowSize);
	void setNextTexture(const std::string &path, const std::string &pathInv);
	void setPrevTexture(const std::string &path, const std::string &pathInv);
	void setBackTexture(const std::string &path, const std::string &pathInv);
	int run(sf::Vector2f mousePos);
};

#endif /* HowToPlay_hpp */

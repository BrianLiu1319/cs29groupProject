#ifndef Credits_hpp
#define Credits_hpp

#include "Menu.hpp"

class Credits : public Menu {
private:
	// NOTE: Go to Menu.hpp to change the Folder Path.

	// File Names
	const std::string menuBackgroundTexturePath = assetFolder + "credits menu bg-01.png";
	const std::string backButtonPath = assetFolder + "back button.png";
	const std::string backButtonInvPath = assetFolder + "back button inverted.png";
	const std::string clickSFXPath01 = assetFolder + "click02.wav";

	sf::Texture backTexture, backTextureInv;
	sf::RectangleShape backButton;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Credits(sf::Vector2f windowSize);
	void setBackTexture(const std::string &path, const std::string &pathInv);
	int run(sf::Vector2f mousePos);
};

#endif /* Credits_hpp */

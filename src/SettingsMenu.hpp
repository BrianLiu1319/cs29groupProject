#pragma once

#include "Menu.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class SettingsMenu : public Menu {
	// NOTE: Go to FolderPath.hpp to change the Folder Path.
private:
	const std::string menuBackgroundTexturePath = assetFolder + "settings menu bg-01.png";
	const std::string creditsButtonTexturePath = assetFolder + "credits button.png";
	const std::string creditsButtonTextureInvPath = assetFolder + "credits button inverted.png";
	const std::string howtoButtonTexturePath = assetFolder + "how to button.png";
	const std::string howtoButtonTextureInvPath = assetFolder + "how to button inverted.png";
	const std::string backButtonTexturePath = assetFolder + "back button.png";
	const std::string backButtonTextureInvPath = assetFolder + "back button inverted.png";
	const std::string sfxButtonPath = assetFolder + "sfx on.png";
	const std::string sfxMuteButtonPath = assetFolder + "sfx off.png";
	const std::string sfxButtonInvPath = assetFolder + "sfx on inverted.png";
	const std::string sfxMuteButtonInvPath = assetFolder + "sfx off inverted.png";
	const std::string musicButtonPath = assetFolder + "music on.png";
	const std::string musicMuteButtonPath = assetFolder + "music off.png";
	const std::string musicButtonInvPath = assetFolder + "music on inverted.png";
	const std::string musicMuteButtonInvPath = assetFolder + "music off inverted.png";
	const std::string clickSFXPath01 = assetFolder + "click02.wav";
	const std::string difficultyPath = assetFolder + "difficulty-";
	const std::string nextButtonPath = assetFolder + "next button.png";
	const std::string nextButtonInvPath = assetFolder + "next button inverted.png";
	const std::string prevButtonPath = assetFolder + "prev button.png";
	const std::string prevButtonInvPath = assetFolder + "prev button inverted.png";
	const std::string fontPath = assetFolder + "AnonymousPro-Regular.ttf";

	static const unsigned int numOfDifficulty = 3;
	unsigned int currDifficultyLevel;
	sf::Texture difficultyLevelTextures[numOfDifficulty];
	sf::Texture creditsTexture, howtoTexture, creditsTextureInv, howtoTextureInv, sfxTexture,
	  sfxMuteTexture, sfxTextureInv, sfxMuteTextureInv, musicTexture, musicMuteTexture,
	  musicTextureInv, musicMuteTextureInv, backTexture, backTextureInv, nextTexture, prevTexture,
	  nextTextureInv, prevTextureInv;
	sf::RectangleShape creditsButton, howtoButton, backButton, sfxButton, musicButton,
	  currDifficulty, nextButton, prevButton;
	sf::Font textFont;
	sf::Text text;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool handleSoundButton(sf::RectangleShape &button,
	  const sf::Texture &buttonTexture,
	  const sf::Texture &buttonInvTexture,
	  const sf::Texture &buttonMuteTexture,
	  const sf::Texture &buttonMuteInvTexture,
	  const sf::Vector2f &mousePos);

public:
	SettingsMenu(sf::Vector2f windowSize);
	void setCreditsTexture(const std::string& path, const std::string& pathInv);
	void setHowtoTexture(const std::string& path, const std::string& pathInv);
	void setBackTexture(const std::string& path, const std::string& pathInv);
	void setSfxTexture(const std::string& path,
	  const std::string& pathInv,
	  const std::string& pathMute,
	  const std::string& pathMuteInv);
	void setMusicTexture(const std::string& path,
	  const std::string& pathInv,
	  const std::string& pathMute,
	  const std::string& pathMuteInv);
	void setDifficultyTextures(const std::string& path);
	void setNextTexture(const std::string& path, const std::string& pathInv);
	void setPrevTexture(const std::string& path, const std::string& pathInv);
	void setFont(const std::string& path);
	int run(sf::Vector2f mousePos);
};

#include "GameOver.hpp"

/*********************************
Draws the Game Over screen.
*********************************/
void GameOver::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(background);
  // ADDNEW
  target.draw(clawMark);
  target.draw(confirmButton);
  target.draw(text);
}

/*********************************
Constructor.
 Sets up everything according to the
 window size.
*********************************/
GameOver::GameOver(sf::Vector2f windowSize) : Menu(windowSize), score(0) {
  sf::Vector2f buttonSize(windowSize.x / 1920.0f * 600.0f,
                          windowSize.y / 1080.0f * 135.0f);
  sf::Vector2f centerButtonPos(windowSize.x / 2.0f - buttonSize.x / 2,
                               windowSize.y / 2.0f - buttonSize.y / 2);

  background.setFillColor(sf::Color::Black);

  try {
    setConfirmButtonTexture(confirmButtonPath, confirmButtonInvPath);
    setFont(fontPath);
    setClickSound(clickSFXPath01);

    // ADDNEW
    if (!clawMarkTexture.loadFromFile(clawPath)) {
      throw(clawPath);
    }
    clawMark.setTexture(&clawMarkTexture);
    // ADDNEW
    setGameOverSound();

  } catch (const std::string &fileName) {
    std::cerr << "Unable to open file " << fileName << std::endl;
    std::cerr << "Location: GameOver " << std::endl;
    exit(1);
  }

  setText();
  confirmButton.setSize(sf::Vector2f(buttonSize.x, buttonSize.y));
  confirmButton.setPosition(centerButtonPos.x, centerButtonPos.y);
  confirmButton.setOutlineThickness(buttonSize.y / 20.0f);
  text.setCharacterSize(static_cast<unsigned int>(windowSize.y / 18));
  text.setFillColor(sf::Color(242, 218, 0));
  text.setPosition(windowSize.x / 2.0f - buttonSize.x / 2.0f,
                   windowSize.y * 0.3f);

  // ADDNEW
  clawMark.setSize(sf::Vector2f(buttonSize.x, buttonSize.x));
  // ADDNEW
  clawMark.setPosition(centerButtonPos.x,
                       centerButtonPos.y - clawMark.getSize().y / 2.0f);
}

/*********************************
Sets the texture for the confirm button.
 Throws the path of file if not found.
*********************************/
void GameOver::setConfirmButtonTexture(std::string path, std::string pathInv) {
  if (!confirmButtonTexture.loadFromFile(path.c_str())) {
    throw(std::string(path));
  }
  if (!confirmButtonTextureInv.loadFromFile(pathInv.c_str())) {
    throw(std::string(pathInv));
  }

  confirmButton.setTexture(&confirmButtonTexture);
}

/*********************************
Sets the font for the text.
 Throws the path of file if not found.
*********************************/
void GameOver::setFont(std::string path) {
  if (!textFont.loadFromFile(path.c_str())) {
    throw(std::string(path));
  }
  text.setFont(textFont);
}

/*********************************
Sets the text to read:
 "Game Over...
 Your Score: (score)"
*********************************/
void GameOver::setText() {
  text.setString("Game Over...\nYour Score: " + std::to_string(score));
}

/*********************************
Runs the Game Over screen.
*********************************/
int GameOver::run(sf::Vector2f mousePos) {

  /*
   state:
   0 - Stay on Game Over screen
   1 - Leave Game Over screen
   */
  int state = 0;

  // ADDNEW
  if (!muteSfx && !sfxHasPlayed &&
      gameOverSound.getStatus() != sf::Sound::Playing) {
    gameOverSound.play();
    sfxHasPlayed = true;
  }

  // Handle actions on confirm button
  if (handleButton(confirmButton, confirmButtonTexture, confirmButtonTextureInv,
                   mousePos)) {
    state = 1;
    score = 0;
    setText();

    // ADDNEW
    sfxHasPlayed = false;
    gameOverSound.stop();
  }

  return state;
}

/*********************************
Sets the score shown.
*********************************/
void GameOver::setScore(unsigned int s) {
  score = s;
  setText();
}

// ADDNEW
/*********************************
Sets the sound effect for game over.
*********************************/
void GameOver::setGameOverSound() {
  if (!gameOverSoundBuffer.loadFromFile(gameOverSoundPath)) {
    throw(std::string(gameOverSoundPath));
  }

  gameOverSound.setBuffer(gameOverSoundBuffer);
  gameOverSound.setVolume(15.0f);
}

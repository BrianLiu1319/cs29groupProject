#include "Game.hpp"

Game::Game(sf::Vector2f windowSize) :
    Menu(windowSize), statsDisplay(windowSize), tools(windowSize) {
	try {
		setClickSound(clickSFXPath01);
		setBgMusic();
		setBgTexture(bgTexturePath);
	} catch (const std::string &fileName) {
		std::cerr << "Unable to open the file " << fileName << std::endl;
		std::cerr << "Location: Game" << std::endl;
		exit(1);
	}
}

/*
Generates tiles
*/
vector<Land *> Game::generateLandList() {
	vector<Land *> landList = {};
	sf::Vector2f tempPosition;
	float x = 50.f;
	float y = 50.f;
	for (int i = 0; i < 60; i++) {
		tempPosition.x = x;
		tempPosition.y = y;
		Land *aland = new Land(i, tempPosition);
		landList.push_back(aland);
		y += 94;

		if (y > 480) {
			y = 50;
			x += 74;
		}
	}
	return landList;
}

// This function create a inventory vector which stores all inventory
vector<Inventory *> Game::generateInvenList() {
	vector<Inventory *> InvenList = {};
	Vector2f aPosition;
	Inventory *aInven = nullptr;
	float x = 50;
	float y = 600;
	for (int i = 0; i < 3; i++) {
		aPosition.x = x;
		aPosition.y = y;
		aInven = new Inventory(aPosition, i);
		InvenList.push_back(aInven);
		x += 60;
	}
	return InvenList;
}

/*
Generates Waves of Attackers at random
*/
void Game::simpleAttackerGenerator(vector<Attacker *> &attackers, const vector<Land *> &landList) {
	int numCatsPerWave = 4 + currentWave;

	if (waveStart) {
		statsDisplay.updateWave(currentWave);

		auto temp = generatorClock.restart().asSeconds();
		deltaGenTime += temp;
		waveGenTime += temp;

		float randomTimeframe = rand() % 5 + 10.0f;
		randomTimeframe -= currentWave * 0.5f;

		if (waveGenTime >= randomTimeframe * 8 / difficulty * 1.5f) {
			if (numDogsInBigWave < numCatsPerWave) {
				randomTimeframe *= 0.3f;
				onWave = true;
			} else {
				numDogsInBigWave = 0;
				waveGenTime = 0.0f;
				currentWave++;
				onWave = false;
			}
		}

		if (deltaGenTime >= randomTimeframe / difficulty * 1.5f) {
			int tempLandIndex = static_cast<int>(rand() % landList.size());
			addAttacker(attackers, landList[tempLandIndex]->getVector());
			deltaGenTime = 0;
			if (onWave) numDogsInBigWave++;
		}
	}
}

// Draws, erases if out of screen, and updates accordingly.
void Game::gameClock(RenderWindow &window, vector<Collider *> &things) {
	if (things.empty()) { return; }
	for (int i = 0; i < static_cast<int>(things.size()); i++) {
		things[i]->updateObject();
		// Add dynamic cast for attacker for game over
		if (dynamic_cast<Attacker *>(things[i]) != nullptr) {
			if ((things[i])->getPosition().x > WINDOW_WIDTH + (things[i])->getGlobalBounds().width
			    || (things[i])->getPosition().x < -100) {
				gameOver = true;
				return;
			}
		}
		if ((things[i])->getPosition().x > WINDOW_WIDTH + (things[i])->getGlobalBounds().width
		    || (things[i])->getPosition().x < -100) {
			delete things[i];
			things.erase(things.begin() + i);
		} else {
			threadLock.lock();
			window.draw(*things[i]);
			threadLock.unlock();
		}
	}
}

/*
Get every object and checks if they collide on a tick based system
*/
void Game::checkCollision(vector<Attacker *> &attackers,
  vector<Bullet *> &bullets,
  vector<Defender *> &defenders,
  vector<Coin *> &coins) {
	if (attackers.empty()) { return; }

	for (unsigned int j = 0; j < attackers.size(); j++) {
		for (unsigned int i = 0; i < bullets.size(); i++) {
			if (bullets[i]->getGlobalBounds().intersects(attackers[j]->getGlobalBounds())) {
				bullets[i]->hurt(*(attackers[j]));
				cout << attackers[j]->getHealth() << endl;				

				if (attackers[j]->getHealth() <= 0 && !attackers[j]->isOnDefeat()) {
					attackers[j]->setDefeated();
					if (!muteSfx) attackers[j]->sadSound();
					switch (difficulty) {
						case 1: score += 100; break;
						case 2: score += 200; break;
						case 3: score += 300; break;
						default: break;
					}
					if (attackers[j]->getSpeed() == 25.0f) {
						coins.push_back(new Coin(attackers[j]->getPosition()));
						money += 20;
					} else {
						money += 20;
					}
				}
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
				break;
			}
		}

		if (attackers.empty()) { return; }

		for (unsigned int k = 0; k < defenders.size(); k++) {
			if (defenders.empty()) break;
			if (attackers[j]->getGlobalBounds().intersects(defenders[k]->getGlobalBounds())
			    && defenders[k]->getStatus()) {
				attackers[j]->setDirection(DIR::DIRECTION::TWR);
				if (defenders[k]->getHealth() <= 0 && defenders[k]->getStatus()) {
					if (!muteSfx) defenders[k]->sadSound();

					for (auto & attacker : attackers) {
						if (attacker->getGlobalBounds().intersects(
						      defenders[k]->getGlobalBounds()))
							attacker->setDirection(DIR::DIRECTION::LEFT);
					}

					defenders[k]->setDefeated();
					defenders[k]->setStatus();
				}
			}
		}
	}
}

/*
run the game
*/
int Game::run(RenderWindow &renderWindow) {
	gameOver = false;
	score = 0;
	deltaGenTime = 0.0f;
	waveGenTime = 0.0f;
	generatorClock.restart();
	waveStart = false;
	money = 200;
	statsDisplay.setCountdownMode();
	currentWave = 1;

	sf::Texture textureOfObject;
	if (!textureOfObject.loadFromFile(assetFolder + "bul.png"))
		cout << "Unable to open Bull Txt" << assetFolder + "bul.png" << endl;
	sf::Texture textureOfObject1;
	if(textureOfObject1.loadFromFile(assetFolder + "bul1.png"))
		cout << "Unable to open Bull1 Txt" << assetFolder + "bul1.png" << endl;
	renderWindow.setFramerateLimit(60);	

	if (!font1.loadFromFile(assetFolder + "Font1.ttf"))
		cout << "Unable to open font file " << assetFolder + "Font1.ttf" << endl;

	// int time = 0;
	auto *clock = new Clock();
	sf::Vector2f landPoint(50.f, 50.f);
	Land *aLand = new Land(0, landPoint);

	// Land and Inventory Vectors
	vector<Land *> landList;
	vector<Inventory *> InvenList;

	// Vectors of the main subjects, allBullets // allAttackers // allDefenders
	vector<Bullet *> allBullets = {};
	vector<Attacker *> allAttackers = {};
	vector<Defender *> builtDefenderList = {};
	vector<Coin *> coinsList = {};

	int nInvenselected = -1;
	InvenList = generateInvenList();
	landList = generateLandList();

	// int counter used for selection.
	int nSelected = -1;

	Defender *tempDefender;
	int tempLandIndex;
	while (!gameOver && renderWindow.isOpen()) {
		animationDeltaTime = animationClock.restart().asSeconds();

		if (!muteMusic && bgMusic.getStatus() != sf::Sound::Playing) { bgMusic.play(); }
		if (muteMusic && bgMusic.getStatus() != sf::Sound::Stopped) { bgMusic.stop(); }

		while (renderWindow.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed: renderWindow.close(); break;
				case Event::KeyPressed:
					if ((Keyboard::isKeyPressed(Keyboard::LShift)
					      || Keyboard::isKeyPressed(Keyboard::RShift))
					    && Keyboard::isKeyPressed(Keyboard::X)) {
						gameOver = true;
					}
					if ((Keyboard::isKeyPressed(Keyboard::LShift)
					      || Keyboard::isKeyPressed(Keyboard::RShift))
					    && Keyboard::isKeyPressed(Keyboard::S)) {
						score += 10;
					}
					if ((Keyboard::isKeyPressed(Keyboard::LShift)
					      || Keyboard::isKeyPressed(Keyboard::RShift))
					    && Keyboard::isKeyPressed(Keyboard::C)) {
						money += 10;
					}
					if ((Keyboard::isKeyPressed(Keyboard::LShift)
					      || Keyboard::isKeyPressed(Keyboard::RShift))
					    && Keyboard::isKeyPressed(Keyboard::M)) {
						tempLandIndex = rand() % 30;
						addAttacker(allAttackers, landList[tempLandIndex]->getVector());
					}
					break;
				default: break;
			}
		}

		if (!waveStart) {
			deltaGenTime += generatorClock.restart().asSeconds();
			statsDisplay.updateCountdown(static_cast<int>(deltaGenTime));
			if (deltaGenTime >= 10.0f) {
				waveStart = true;
				deltaGenTime = 0.0f;
				statsDisplay.setWaveMode();
			}
		}
		renderWindow.clear();
		renderWindow.draw(background);

		for (int i = 0; i < 60; i++) { renderWindow.draw(landList[i]->getSprite()); }

		for (int i = 0; i < 3; i++) { renderWindow.draw(InvenList[i]->getSprite()); }

		for (auto &i : coinsList) { renderWindow.draw(i->getSp()); }

		handleTools(builtDefenderList, landList, renderWindow);
		simpleAttackerGenerator(allAttackers, landList);

		// Checks to see if you clicked a inventory dog.
		if (Mouse::isButtonPressed(sf::Mouse::Left)) {
			Vector2i mousePressPosition = Mouse::getPosition(renderWindow);
			for (int i = 0; i < 3; i++) {
				Sprite InvenSp = InvenList[i]->getSprite();
				if (InvenSp.getGlobalBounds().contains(float(mousePressPosition.x),
				      float(mousePressPosition.y))) {
					if (!muteSfx && click.getStatus() != sf::Sound::Playing) click.play();
					nInvenselected = i;
					break;
				}
			}
		}

		// Checks where you clicked to select a grid slot to place tower.
		if (Mouse::isButtonPressed(sf::Mouse::Left) && nInvenselected != -1)

		{
			Vector2i mouseRepostion = Mouse::getPosition(renderWindow);

			for (int i = 0; i < 60; i++) {
				Sprite landSprit = landList[i]->getSprite();
				if (landSprit.getGlobalBounds().contains(static_cast<float>(mouseRepostion.x),
				      static_cast<float>(mouseRepostion.y))) {
					if (!muteSfx && click.getStatus() != sf::Sound::Playing) click.play();
					nSelected = i;
					break;
				}
			}
		}

		// If you selected a inventory dog AND a grid spot, create and place a tower
		// there.
		if (nSelected >= 0 && nSelected < 60 && nInvenselected < 3 && nInvenselected > -1
		    && landList[nSelected]->getEmpty()) {
			if (nInvenselected == 0 && money >= 40) {
				tempDefender = new Defender(landList[nSelected]->getVector());
				landList[nSelected]->setEmpty(false);
				tempDefender->setLandIndex(nSelected);
				builtDefenderList.push_back(tempDefender);

				money -= tempDefender->getCost();

				if (!muteSfx) tempDefender->bark();

			}

			else if (nInvenselected == 1 && money >= 60) {
				tempDefender = new Defender(landList[nSelected]->getVector(), 2.0f);
				landList[nSelected]->setEmpty(false);

				tempDefender->setLandIndex(nSelected);
				builtDefenderList.push_back(tempDefender);

				money -= tempDefender->getCost();

				if (!muteSfx) tempDefender->bark();

			}

			else if (nInvenselected == 2 && money >= 80) {
				tempDefender = new Defender(landList[nSelected]->getVector(), 2);
				landList[nSelected]->setEmpty(false);

				tempDefender->setLandIndex(nSelected);
				builtDefenderList.push_back(tempDefender);

				money -= tempDefender->getCost();

				if (!muteSfx) tempDefender->bark();
			}
			nSelected = -1;
			nInvenselected = -1;
		}

		if (!builtDefenderList.empty()) {
			for (auto &item : builtDefenderList) {
				if (clock->getElapsedTime().asMilliseconds() >= 2000) {
					cout << allBullets.size() << endl;
					if (clock->getElapsedTime().asMilliseconds() >= 2000) {
						if (item->getCost() == 40) {
							auto loc = item->getPosition();
							loc.x += 45;
							auto *temp = new Bullet(textureOfObject, loc);
							allBullets.push_back(temp);
						} else if (item->getCost() == 80) {
							auto loc = item->getPosition();
							loc.x += 45;
							auto *temp = new Bullet(textureOfObject1, loc, 2);
							allBullets.push_back(temp);
						}

						for (auto &attacker : allAttackers) {
							if (attacker->getGlobalBounds().intersects(item->getGlobalBounds())) {
								attacker->hurt(*item);
								cout << item->getHealth() << endl;
							}
						}
					}
				}
			}

			if (clock->getElapsedTime().asMilliseconds() >= 2000) { clock->restart(); }
		}
		if (Keyboard::isKeyPressed(Keyboard::C)) {
			money += coinsList.size() * 60;
			for (auto &i : coinsList) { delete i; }
			coinsList.clear();
		}

		simpleAttackerGenerator(allAttackers, landList);

		// Update Animations and erase defeated Cats/Dogs
		updateAnimations(builtDefenderList, allAttackers, landList);

		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(allBullets));
		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(builtDefenderList));
		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(allAttackers));
		checkCollision(allAttackers, allBullets, builtDefenderList, coinsList);

		statsDisplay.updateMoney(money);
		statsDisplay.updateScore(score);
		renderWindow.draw(statsDisplay);

		renderWindow.display();
	}
	if (bgMusic.getStatus() != sf::Sound::Stopped) { bgMusic.stop(); }
	for (auto &allAttacker : allAttackers) { delete allAttacker; }
	for (auto &allBullet : allBullets) { delete allBullet; }
	for (auto &i : builtDefenderList) { delete i; }
	delete clock;
	delete aLand;

	return 0;
}

/*
Add Random Attacker onto field
*/
void Game::addAttacker(vector<Attacker *> &attackers, Vector2f a) {
	int temp1 = rand() % 3;
	if (temp1 == 0) {
		auto *temp = new Attacker(a, assetFolder + "catSprites1.png");
		attackers.push_back(temp);
		if (!muteSfx) temp->meow();
	} else if (temp1 == 1) {
		auto *temp = new Attacker(a, assetFolder + "catSprites2.png");
		attackers.push_back(temp);
		if (!muteSfx) temp->meow();
	} else if (temp1 == 2) {
		auto *temp = new Attacker(a, assetFolder + "catSprites3.png");
		attackers.push_back(temp);
		if (!muteSfx) temp->meow();
	}
}

/*
Mute music
*/
void Game::toggleMuteMusic() {
	if (muteMusic) {
		muteMusic = false;
	} else {
		muteMusic = true;
	}
}

/*
Set the BG music of game and main menu
*/
void Game::setBgMusic() {
	if (!bgMusic.openFromFile(bgMusicPath)) { throw(std::string(bgMusicPath)); }

	bgMusic.setLoop(true);
	bgMusic.setVolume(15.0f);
}

/*
Update animation of object based on state ( death, moving , attacking ... etc )
*/
void Game::updateAnimations(vector<Defender *> &defenders,
  vector<Attacker *> &attackers,
  vector<Land *> &landList) {
	for (int i = 0; i < static_cast<int>(attackers.size()); i++) {
		if (attackers[i]->isDefeated()) {
			threadLock.lock();
			delete attackers[i];
			attackers.erase(attackers.begin() + i);
			threadLock.unlock();
		} else {
			attackers[i]->updateAnimation(animationDeltaTime);
		}
	}

	for (int i = 0; i < static_cast<int>(defenders.size()); i++) {
		if (defenders[i]->isDefeated()) {
			int landIndex = defenders[i]->getLandIndex();
			if (static_cast<int>(landList.size()) > landIndex) {
				landList[landIndex]->setEmpty(true);
			}
			delete defenders[i];
			defenders.erase(defenders.begin() + i);
		} else {
			defenders[i]->updateAnimation(animationDeltaTime);
		}
	}
}

/*
Allows interaction of tool bar ( whistle and heal )
*/
void Game::handleTools(vector<Defender *> &defenders,
  vector<Land *> &landList,
  sf::RenderWindow &window) {
	window.draw(tools);
	tools.run(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
	Vector2i mousePressPosition = Mouse::getPosition(window);

	if (tools.whistleSelected()) {
		if (mouseStartClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mouseStartClick = false;
			if (!muteSfx) click.play();

			for (int i = 0; i < static_cast<int>(landList.size()); i++) {
				if ((landList[i]->getSprite())
				      .getGlobalBounds()
				      .contains(float(mousePressPosition.x), float(mousePressPosition.y))) {
					for (int j = 0; j < static_cast<int>(defenders.size()); j++) {
						if (defenders[j]->getGlobalBounds().contains(
						      static_cast<float>(mousePressPosition.x),
						      static_cast<float>(mousePressPosition.y))) {
							delete defenders[j];
							defenders.erase(defenders.begin() + j);
							landList[i]->setEmpty(true);
							money += tools.getWhistleRefund();
							tools.deselectAll();
						}
					}
				}
			}
		} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseStartClick) {
			mouseStartClick = true;
			tools.deselectAll();
		}
	}

	if (tools.healthSelected()) {
		if (mouseStartClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mouseStartClick = false;
			if (!muteSfx) click.play();

			for (auto & defender : defenders) {
				if (defender->getGlobalBounds().contains(
				      static_cast<float>(mousePressPosition.x),
				      static_cast<float>(mousePressPosition.y))) {
					if (money >= tools.getHealthCost()) {
						(*defender).increaseHealth(100);

						money -= tools.getHealthCost();
					}
				}
			}
			tools.deselectAll();
		}
	} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseStartClick) {
		mouseStartClick = true;
		tools.deselectAll();
	}
}

#include "Game.hpp"

Game::Game(Vector2f windowSize) : Menu(windowSize) {
	try {
		setClickSound(clickSFXPath01);
	} catch (const string &fileName) {
		cerr << "Unable to open the file " << fileName << endl;
		cerr << "Location: Game" << endl;
		exit(1);
	}
}

// this function calculate how many towers we could build. Currently I just set it to
// just return 1, since I haven't made the cost yet.
// PROBLEM TO FIX: Add a Cost to the Defender class and replace this
int Game::howManyTower() {  // function with a defender instead of tower.
	/*
	Tower* aTower = new Tower();       // Use this as a reference and replace with
	Defender instead. int cost = aTower->getCost(); vector<Tower*> TowerList = {};
	int amount = money / cost;
	//return amount;
	*/
	return 1;  // Just returns 1 for test purposes. Remove this for "amount" instead.
}

/*
// Fire function with the defender class. Responsible for creating new Bullets and
// put them in the Bullet Vector. PROBLEM: Bullet still needs to take a position
// vector from the Defender. Once we make the bullet, then we insert it Perhaps make
// another function for addBullet(allBullets, bullet) or just add it directly to the
// vector without the use of a function.

void Game::fire(Clock *clock, Defender *fireTower, vector<Bullet *> bulletList) {
    Defender t = *fireTower;
    if (clock->getElapsedTime().asMilliseconds()
        >= 1000) {  // if time > = 5 sec // Time constraint, ho
        // Bullet mBullet = Bullet(t.getPosition()); //
        // addBullet(bulletList, mBullet);// push a bullet into list, but we need to
        // add a specific bullet... addBullet(bulletList);
        auto *temp = new Bullet(allTextures.getBullet(),fireTower->getPosition());
        bulletList.push_back(temp);

        // Now we need to add a bullet with specific spot based on the tower
        // position...
    }
    // Vector2f pt = aBullet.getSp()->getPosition();
}
*/

// This function define a textview that shows the how much money user has.
void Game::showMoney(int money, RenderWindow &renderWindow) {
	Text showMoney;
	string show = "Money:  " + to_string(money) + "\nScore:  " + to_string(score);
	showMoney.setFont(font1);
	showMoney.setFillColor(Color::Red);
	showMoney.setString(show);
	showMoney.setPosition(renderWindow.getSize().x - showMoney.getLocalBounds().width,
	  renderWindow.getSize().y - showMoney.getLocalBounds().height);
	showMoney.setCharacterSize(20);
	showMoney.setStyle(Text::Regular);
	renderWindow.draw(showMoney);
}

// Draws, erases if out of screen, and updates accordingly.
void Game::gameClock(RenderWindow &window, vector<Collider *> &things) {
	if (things.empty()) { return; }
	for (unsigned int i = 0; i < things.size(); i++) {
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
			things.erase(things.begin() + i);
		} else {
			window.draw(*things[i]);
		}
	}
}

void Game::checkCollision(vector<Attacker *> &attackers,
  vector<Bullet *> &bullets,
  vector<Defender *> &defenders) {
	if (attackers.empty()) { return; }
	for (unsigned int j = 0; j < attackers.size(); j++) {
		for (unsigned int i = 0; i < bullets.size(); i++) {
			if (bullets[i]->getGlobalBounds().intersects(attackers[j]->getGlobalBounds())) {
				bullets[i]->hurt(*(attackers[j]));
				cout << attackers[j]->getHealth() << endl;
				if (attackers[j]->getHealth() <= 0) { attackers.erase(attackers.begin() + j); }
				bullets.erase(bullets.begin() + i);
				break;
			}
		}

		if (attackers.empty()) { return; }

		// DEFENDER GONE STOPS RUNNING
		for (unsigned int k = 0; k < defenders.size(); k++) {
			if (defenders.empty()) break;
			if (attackers[j]->getGlobalBounds().intersects(defenders[k]->getGlobalBounds())) {
				attackers[j]->setDirection(TWR);
				if (defenders[k]->getHealth() <= 0) {
					// iterate through all attackers again//
					// If bool stops,
					for (auto &attacker : attackers) {
						if (attacker->getGlobalBounds().intersects(defenders[k]->getGlobalBounds()))
							attacker->setDirection(LEFT);
					}
					defenders.erase(defenders.begin() + k);
					break;
				}
			}
		}
	}
}

void Game::addAttacker(vector<Attacker *> &attackers, const Texture &attackerText, Vector2f loc) {
	auto temp = new Attacker(attackerText, loc);
	attackers.push_back(temp);
}

void Game::addDefender(vector<Defender *> &towers, const Texture &towerTexture, Vector2f loc) {
	auto temp = new Defender(towerTexture, loc);
	towers.push_back(temp);
}

void Game::toggleMuteSfx() {
	if (muteSfx) {
		muteSfx = false;
	} else {
		muteSfx = true;
	}
}

int Game::run(RenderWindow &renderWindow) {
	gameOver = false;
	score = 0;
	renderWindow.setVerticalSyncEnabled(true);
	renderWindow.setFramerateLimit(60);
	if (!font1.loadFromFile("assets/Font1.ttf")) cerr << "error loading font " << endl;
	int towerInStore = 2;
	auto *clock = new Clock();

	float x = 50;
	float y = 600;
	for (int i = 0; i < 2; i++) {
		auto  point = Vector2f (x,y);
		auto aInven = new Inventory(point, i, allTextures.getInv());
		invenList.push_back(aInven);
		x += 60;
	}

	Vector2f tempPosition;
	x = 50;
	y = 50;
	for (int i = 0; i < 60; i++) {
		tempPosition.x = x;
		tempPosition.y = y;
		Land *aland = new Land(i, tempPosition, &allTextures);
		landList.push_back(aland);
		y += 94;
		// Here, it checks if the grid doesn't exist and we go back down.
		if (y > 480) {
			y = 50;
			x += 74;
		}
	}

	/* // Unused but left for archive
	vector<Tower*> towerList;        //This ia a vector stores all towers
	vector<Tower*> builtTowerList;// this a vector only stores the towers which has
	been built;
	*/

	// Vectors of the main subjects, allBullets // allAttackers // allDefenders

	// List of all defenders. Could implement this in the future.
	// Have a separate list for built Towers to differentiate.

	int nInvenselected = -1;  // This int is a counter; represent the Inventory user
	                          // selected; if user didn't select; it is -1;

	// allDefenders = generateTowerList(landList);    // create towerList, maybe this
	// can be of use?

	// Line to use for separating space between inventory and grid? Unsure
	Vertex line[] = {Vertex(Vector2f(0, 6 * landList[0]->getSprite().getLocalBounds().height)),
	  Vertex(Vector2f(renderWindow.getSize().x,	6 * landList[0]->getSprite().getLocalBounds().height))};

	line->color = Color::White;

	// int counter used for selection.
	int nSelected = -1;

	while (!gameOver && renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed: renderWindow.close(); break;
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::M)) {
						auto tempLandIndex = rand() % 60;
						addAttacker(allAttackers,
						  allTextures.getAttacker(),
						  landList[tempLandIndex]->getPositionofLand());
					}
				default: break;
			}
		}

		// std::cout << "Elapsed time in microseconds: " <<
		// clock->getElapsedTime().asMilliseconds() << std::endl;
		renderWindow.clear();

		showMoney(money, renderWindow);

		// draw the landList(grid) by a for loop
		for (auto item : landList) { renderWindow.draw(item->getSprite()); }

		// draw InvenList below the grid
		for (auto item : invenList) { renderWindow.draw(item->getSprite());}

		// Checks to see if you clicked a inventory dog.
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i mousePressPosition = Mouse::getPosition(renderWindow);
			for (int i = 0; i < 2; i++) {
				Sprite InvenSp = invenList[i]->getSprite();
				if (InvenSp.getGlobalBounds().contains(mousePressPosition.x,
				      mousePressPosition.y))  // if the range of a inventory contain
				                              // the position of mouse
				{
					if (!muteSfx && click.getStatus() != Sound::Playing) click.play();
					if (towerInStore > 0) {
						nInvenselected = i;  // the selected Inventory is i
					}
					break;
				}
			}
		}

		// Checks where you clicked to select a grid slot to place tower.
		if (Mouse::isButtonPressed(Mouse::Left) && nInvenselected != -1)  // mouse event
		{
			Vector2i mousePostion
			  = Mouse::getPosition(renderWindow);  // get the relative position of mouse (get where
			                                       // custom release button)
			// that's also where user want to build a tower

			for (int i = 0; i < 60; i++)  // traverse the land list
			{
				Sprite landSprit = landList[i]->getSprite();
				if (landSprit.getGlobalBounds().contains(mousePostion.x,
				      mousePostion.y))  // if the range of land contain the position of mouse
				{
					if (!muteSfx && click.getStatus() != Sound::Playing) click.play();
					nSelected = i;  // the selected land is i
					break;
				}
			}
		}

		// If you selected a inventory dog AND a grid spot, create and place a tower
		// there.
		if (nSelected >= 0 && nSelected < 60 && nInvenselected < 2
		    && nInvenselected > -1)  // make sure the selected code is inthe range of
		                             // 0-30, the inventory shouldnt be -1
		{
			if (landList[nSelected]->getEmpty()) {
				landList[nSelected]->setEmpty(false);  // set the empty of a land to false, prevent
				                                       // from being repeatedly use
				addDefender(allDefenders,allTextures.getTower(),landList[nSelected]->getPositionofLand());
				// money -= towerList[nSelected]->getCost();        // user' money
				// should minus the cost of selected tower default cost of a tower is
				// 40; PROBLEM: Work on money ^, consider working on Defender
				// functions with cost members.

				nInvenselected = -1;  // now we finish all things we should make nInven back to
				                      // -1; To prepare for next action;
				nSelected = -1;       // the selected land should also back to -1
				towerInStore = howManyTower();  // this statement get how many tower
				                                // we can build with rest money
			}
		}

		// Fires every 1 second a bullet. Currently, the fire function creates
		// bullets in the same spot PROBLEM: Makes bullets position in it's
		// constructor take the vector of Tower.
		if (!allDefenders.empty())  // If the number of towers that have been
		                            // built is not zero, we fire
		{
			for (auto &defender : allDefenders) {
				if (clock->getElapsedTime().asMilliseconds() >= 2000) {
					cout << allBullets.size() << endl;
					if (clock->getElapsedTime().asMilliseconds()
					    >= 2000) {  // if time > = 5 sec
						defender->fire(allBullets,allTextures.getBullet());
						for (auto &attacker : allAttackers) {
							// Purpose is to check for collision in here.
							if (attacker->getGlobalBounds().intersects(
							      defender->getGlobalBounds())) {
								// allAttackers[l]->setDirection(TWR);
								// allDefenders[i]->hurt(*(allAttackers[l]));
								attacker->hurt(*defender);
							}
						}
					}
				}
			}

			if (clock->getElapsedTime().asMilliseconds() >= 2000) { clock->restart(); }
		}

		// Use this to update, erase, and draw all the respective Bullets, Defenders,
		// and Attackers.
		renderWindow.draw(line,2,sf::Lines);
		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(allBullets));
		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(allDefenders));
		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(allAttackers));
		checkCollision(allAttackers, allBullets, allDefenders);
		renderWindow.display();
	}

	return 0;
}

Game::~Game() {
	for (auto item : allAttackers) { delete item;}
	for (auto item : allBullets) { delete item;}
	for (auto item : allDefenders) { delete item;}
	for (auto item : landList) { delete item;}
	for (auto item : invenList) { delete item;}

}

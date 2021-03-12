#include "Collider.hpp"
#include "Inventory.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace sf;

// Tommy: I made some comments regarding how this program works and all, if it
// says PROBLEM: it's an issue that still needs to be addressed. Also, some of
// the image paths are C:/temp which was for me to use and I apologize for
// making it convenient like that >_<.
vector<Land *> genrateLandList(AllTextures *texture);
Defender *defenderBuild(Land *aLand, AllTextures *texture);
void addAttacker(vector<Attacker *> &attackers, const Texture &attackerText, Vector2f loc);
void gameClock(RenderWindow &window, vector<Collider *> &things);
void checkCollision(vector<Attacker *> &attackers, vector<Bullet *> &bullets, vector<Defender *> &defenders);
vector<Defender *> generateTowerList(vector<Land *> landList, AllTextures *texture);
RenderWindow renderWindow(VideoMode(1000, 1000), "SFML Demo");
Event event {};
Font font1 {};
// Land, Money, and Thread variables
int money = 200;

// This function create a inventory vector which stores all inventory
vector<Inventory *> generateInvenList() {
	vector<Inventory *> InvenList = {};
	Vector2f aPosition;
	Inventory *aInven = NULL;
	int x = 50;
	int y = 600;
	for (int i = 0; i < 2; i++) {
		aPosition.x = x;
		aPosition.y = y;
		aInven = new Inventory(aPosition, i);
		InvenList.push_back(aInven);
		x += 60;
	}
	return InvenList;
}


// this function cauculate how many towers we could build. Currently I just set
// it to just return 1, since I haven't made the cost yet.
int howManyTower(int money) {
	/* PROBLEM TO FIX: Add a Cost to the Defender class and replace
	 this function with a defender instead of tower.
	Tower* aTower = new Tower();       // Use this as a reference and replace with
	Defender instead. int cost = aTower->getCost(); vector<Tower*> TowerList = {};
	int amount = money / cost;
	//return amount;
	*/
	return 1;  // Just returns 1 for test purposes. Remove this for "amount"
	           // instead.
}


// Fire function with the defender class. Responsible for creating new Bullets
// and put them in the Bullet Vector. PROBLEM: Bullet still needs to take a
// position vector from the Defender. Once we make the bullet, then we insert it
// Perhaps make another function for addBullet(allBullets, bullet) or just add
// it directly to the vector without the use of a function.

void fire(Clock *clock, Defender *fireTower, vector<Bullet *> bulletList, AllTextures *texture) {
	Defender t = *fireTower;
	cout << bulletList.size() << endl;
	int a = clock->getElapsedTime().asMilliseconds();

	if (clock->getElapsedTime().asMilliseconds() >= 1000) {  // if time > = 5 sec // Time constraint, ho
		cout << "Fire away!" << endl;
		// Bullet mBullet = Bullet(t.getPosition()); //
		// addBullet(bulletList, mBullet);// push a bullet into list, but we need to
		// add a specific bullet... addBullet(bulletList);
		t.fire(bulletList, texture->getBullet());
		// Now we need to add a bullet with specific spot based on the tower
		// position...
	}
	cout << "End of fire" << endl;
	// Vector2f pt = aBullet.getSp()->getPosition();
}

// this function draw all the towers which we have alrady built. Currently we
// don't need this, only for testing purposes.
void drawBuiltDefender(vector<Defender *> builtTowerList) {
	for (auto item : builtTowerList) {
		renderWindow.draw(*item);  ////////// work on this!!!
	}
}

// This function define a textview that shows the how much money user has.
void showMoney(int val) {
	Text showMoney;
	string show = "Money:  " + to_string(val);
	showMoney.setFont(font1);
	showMoney.setFillColor(Color::Red);
	showMoney.setString(show);
	showMoney.setPosition(800, 100);
	showMoney.setCharacterSize(20);
	showMoney.setStyle(Text::Regular);
	renderWindow.draw(showMoney);
}

int main() {
	auto myTextures = AllTextures();
	font1.loadFromFile("res/Font1.ttf");
	// textureOfObject
	renderWindow.setVerticalSyncEnabled(true);
	renderWindow.setFramerateLimit(60);
	int towerInStore = 2;
	Clock *clock = new Clock();
	// define a land
	Vector2f landPoint(50.f, 50.f);

	// Land and Inventory Vectors
	vector<Land *> landList;  // vector to store the land, you can think this
	                          // vector is the grass grid!
	vector<Inventory *> InvenList;

	/* // Unused but left for archive
	vector<Tower*> towerList;		//This ia a vector stores all towers
	vector<Tower*> builtTowerList;// this a vector only stores the towers which
	has been built;
	*/

	// Vectors of the main subjects, allBullets // allAttackers // allDefenders
	vector<Bullet *> allBullets = {};
	vector<Attacker *> allAttackers = {};
	vector<Defender *> allDefenders = {};       // List of all defenders. Could implement this in the future.
	vector<Defender *> builtDefenderList = {};  // Have a seperate list for built Towers to differentiate.

	int nInvenselected = -1;                  // This int is a counter; represent the Inventory
	                                          // user selected; if user didnt select; it is -1;
	InvenList = generateInvenList();          // creat the Inventory list
	landList = genrateLandList(&myTextures);  // creat land list

	// allDefenders = generateTowerList(landList);	// creat towerList, maybe
	// this can be of use?

	// Line to use for seperating space between inventory and grid? Unsure
	Vertex line[] = {Vertex(Vector2f(0, 0)), Vertex(Vector2f(500, 500))};

	line->color = Color(256, 256, 0);

	// int counter used for selection.
	int nSelected = -1;

	// Temp values used in the main.

	// Tower* pTower = NULL;
	// Tower* pTowerHolder = NULL;
	Defender *tempDefender = NULL;
	Defender *pDefenderHolder = NULL;
	int tempLandIndex;
	Vector2f landTempVec;
	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed: renderWindow.close(); break;
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::M)) {
						tempLandIndex = rand() % 30;
						landTempVec = landList[tempLandIndex]->getPositionofLand();
						addAttacker(allAttackers,
						  myTextures.getAttacker(),
						  landTempVec);  // this should be called with game clock
					}
				default: break;
			}
		}
		//
		std::cout << "Elapsed time in microseconds: " << clock->getElapsedTime().asMilliseconds() << std::endl;
		renderWindow.clear();

		showMoney(money);
		// draw the landList(grid) by a for loop
		for (int i = 0; i < 30; i++) { renderWindow.draw(landList[i]->getSprite()); }

		// draw InvenList below the grid
		for (int i = 0; i < 2; i++) { renderWindow.draw(InvenList[i]->getSprite()); }

		// Checks to see if you clicked a inventory dog.
		if (event.type == Event::EventType::MouseButtonPressed) {
			Vector2i mousePressPosition = Mouse::getPosition(renderWindow);
			for (int i = 0; i < 2; i++) {
				Sprite InvenSp = InvenList[i]->getSprite();
				if (InvenSp.getGlobalBounds().contains(mousePressPosition.x,
				      mousePressPosition.y))  // if the range of a inventory contain
				                              // the position of mouse
				{
					if (towerInStore > 0) {
						nInvenselected = i;  // the selected Inventory is i
					}
					break;
				}
			}
		}

		// Checks where you clicked to select a grid slot to place tower.
		if (event.type == Event::EventType::MouseButtonReleased && nInvenselected != -1)  // mouse event
		{
			Vector2i mouseRepostion = Mouse::getPosition(renderWindow);  // get the relative position of mouse (get
			                                                             // where custom release button)
			// that's also where user want to build a tower

			for (int i = 0; i < 30; i++) { // traverse the land list
				if (landList[i]->getSprite().getGlobalBounds().contains(mouseRepostion.x,mouseRepostion.y)){  // if the range of land contain the position of mouse
									nSelected = i;  // the selected land is i
					break;
				}
			}
		}

		// If you selected a inventory dog AND a grid spot, create and place a tower
		// there.
		if (nSelected >= 0 && nSelected < 30 && nInvenselected < 2
		    && nInvenselected > -1)  // make sure the selected code is inthe range of
		                             // 0-30, the inventory shouldnt be -1
		{
			tempDefender = defenderBuild(landList[nSelected], &myTextures);  //
			if (landList[nSelected]->getEmpty()) {
				landList[nSelected]->setEmpty(false);  // set the empty of a land to false, prevent from being
				                                       // repeatly use
				builtDefenderList.push_back(tempDefender);

				// money -= towerList[nSelected]->getCost();		// user' money
				// should minus the cost of selected tower default cost of a tower is 40;
				// PROBLEM: Work on money ^, consider working on Defender functions with
				// cost members.

				nInvenselected = -1;                 // now we finish all things we should make nInven
				                                     // back to -1; To prepare for next action;
				nSelected = -1;                      // the selected land should also back to -1
				towerInStore = howManyTower(money);  // this statement get how many tower
				                                     // we can build with rest money
			}
		}

		// Fires every 1 second a bullet. Currently, the fire function creates
		// bullets in the same spot PROBLEM: Makes bullets position in it's
		// constructor take the vector of Tower.
		if (!builtDefenderList.empty())  // If the number of towers that have been built is not zero, we fire
		{
			for (int i = 0; i < builtDefenderList.size(); i++) {
				pDefenderHolder = builtDefenderList[i];

				if (clock->getElapsedTime().asMilliseconds() >= 2000) {
					cout << allBullets.size() << endl;

					if (clock->getElapsedTime().asMilliseconds() >= 2000) {  // if time > = 5 sec // Time constraint, ho

						auto *temp = new Bullet(myTextures.getBullet(), pDefenderHolder->getPosition());
						allBullets.push_back(temp);

						for (int l = 0; l < allAttackers.size(); l++) {
							// Purpose is to check for collision in here.
							if (allAttackers[l]->getGlobalBounds().intersects(
							      builtDefenderList[i]->getGlobalBounds())) {
								// allAttackers[l]->setDirection(TWR);
								// builtDefenderList[i]->hurt(*(allAttackers[l]));

								allAttackers[l]->hurt(*(builtDefenderList[i]));
								cout << builtDefenderList[i]->getHealth() << endl;

								cout << "HITTEM!! "
								     << "THE DOG HP IS NOW " << builtDefenderList[i]->getHealth() << endl;
							}
						}
						// addBullet(allBullets); //For test purposes
						// Add damage check for tower
					}
					cout << "End of fire" << endl;

					// fire(clock, pDefenderHolder, allBullets);
				}
			}

			if (clock->getElapsedTime().asMilliseconds() >= 2000) { clock->restart(); }
		}

		// Use this to update, erase, and draw all the respective Bullets,
		// Defenders, and Attackers.

		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(allBullets));
		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(builtDefenderList));
		gameClock(renderWindow, reinterpret_cast<vector<class Collider *> &>(allAttackers));
		checkCollision(allAttackers, allBullets, builtDefenderList);
		renderWindow.display();
	}
	return 0;
}

// Draws, erases if out of screen, and updates accordingly.
void gameClock(RenderWindow &window, vector<Collider *> &things) {
	if (things.empty()) { return; }
	for (int i = 0; i < things.size(); i++) {
		things[i]->updateObject();
		// Add dynamic cast for attacker for game over
		if (dynamic_cast<Attacker *>(things[i]) != nullptr) {
			if ((things[i])->getPosition().x > WINDOW_WIDTH + (things[i])->getGlobalBounds().width
			    || (things[i])->getPosition().x < -100) {
				exit(420);
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

void checkCollision(vector<Attacker *> &attackers, vector<Bullet *> &bullets, vector<Defender *> &defenders) {
	// Add a temp to all the vectors to ensure never crash!
	if (attackers.empty()) { return; }

	for (int j = 0; j < attackers.size(); j++) {
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i]->getGlobalBounds().intersects(attackers[j]->getGlobalBounds())) {
				bullets[i]->hurt(*(attackers[j]));
				cout << attackers[j]->getHealth() << endl;
				if (attackers[j]->getHealth() <= 0) { attackers.erase(attackers.begin() + j); }
				bullets.erase(bullets.begin() + i);
				break;
			}
		}

		if (attackers.empty()) { return; }

		// DEFNDER GONE STOPS RUNNING
		for (int k = 0; k < defenders.size(); k++) {
			if (attackers[j]->getGlobalBounds().intersects(defenders[k]->getGlobalBounds())) {
				cout << "Cmere" << endl;
				attackers[j]->setDirection(TWR);
				if (defenders[k]->getHealth() <= 0) {
					// iterate through all attackers again//
					// If bool stops,
					for (int z = 0; z < attackers.size(); z++) {
						if (attackers[z]->getGlobalBounds().intersects(defenders[k]->getGlobalBounds()))
							attackers[z]->setDirection(LEFT);
					}
					defenders.erase(defenders.begin() + k);
					break;
				}
			}
		}
	}
}

// Same as above but with Defender class instead of the old tower class.
// Generate the list of towers. Prebuilds a list of towers to use.
// Used to just add towers to built tower list. Currently, I don't use this, for
// testing purposes.
/*
vector<Defender *> generateTowerList(vector<Land *> landList, AllTextures *texture) {
	vector<Defender *> towerList = {};
	Vector2f temp;
	for (int i = 0; i < 30; i++) {
		Defender *aInven = new Defender(texture->getTower(), landList[i]->getPositionofLand());
		towerList.push_back(aInven);
	}
	return towerList;
}
*/

// Take a selected land and build the tower on this land. Return the pointer of
// this tower PROBLEM: Issue is dynanmic memory. We need to delete this after!!!
Defender *defenderBuild(Land *aLand, AllTextures *texture) {
	auto *aDefender = new Defender(texture->getTower(), aLand->getPositionofLand());
	return aDefender;
}

// Generate the land list to build grid(map);
vector<Land *> genrateLandList(AllTextures *texture) {
	vector<Land *> landList = {};
	Vector2f tempPosition;
	int x = 50;
	int y = 50;
	for (int i = 0; i < 30; i++) {
		tempPosition.x = x;
		tempPosition.y = y;
		Land *aland = new Land(i, tempPosition, texture);
		landList.push_back(aland);
		y += 94;

		if (y > 480)  // Here, it checks if the grid doesn't exist and we go back down.
		{
			y = 50;
			x += 74;
		}
	}
	return landList;
}

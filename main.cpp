/********************
 *  Deniz Erisgen
 *  Group Project
 *  Compiler:GCC
********************/
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include "Collider.hpp"



using namespace sf;
using std::cout;
using std::vector;
using std::endl;

void gameClock(RenderWindow &window, vector<Collider*> &things);

void addBullet(vector<Bullet*> &things);

void addAttacker(vector<Attacker*> &attackers);

void checkCollision(vector<Attacker*> &attackers, vector<Bullet*> &bullets);

int main() {
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DogsnCats", Style::Close | Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	vector<Bullet*> allBullets;
	vector<Attacker*> allAttackers;
//	Bullet bulletzz = Bullet();
//	Attacker cAttacker = Attacker();
//	allBullets.push_back(&bulletzz);
//	allAttackers.push_back(&cAttacker);
	while (window.isOpen()) {
		Event event {};
		while (window.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;
				case Event::MouseButtonPressed:
					break;
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::M))
						addAttacker(allAttackers);  // this should be called with game clock
					else if (Keyboard::isKeyPressed(Keyboard::C)) {
						addBullet(allBullets);      // this should be called with game clock
					} else if (Keyboard::isKeyPressed(Keyboard::Right))
					if (Keyboard::isKeyPressed(Keyboard::Left))
					if (Keyboard::isKeyPressed(Keyboard::Up))
					if (Keyboard::isKeyPressed(Keyboard::Down))
					break;
				default:
					break;
			}
		}
		window.clear();
		gameClock(window, reinterpret_cast<vector<class Collider*> &> (allAttackers));
		gameClock(window, reinterpret_cast<vector<class Collider*> &> (allBullets));
		checkCollision(allAttackers, allBullets);
		window.display();
//		for (auto item : allAttackers) {
//			cout << "atackers = "<< item << endl;
//		}
//		for (auto item : allBullets) {
//			cout << "Bullets = "<< item << endl;
//		}
	}
	return 0;
}
// call to update funcs of all items in vector of ALL things
void gameClock(RenderWindow &window, vector<Collider*> &things) {
	for (auto it = things.begin() ; it != things.end() ; it++) {
		if (*it == nullptr) return;
		(*it)->updateObject();
		if ((*it)->getPosition().x > WINDOW_WIDTH + (*it)->getGlobalBounds().width || (*it)->getPosition().x < -100) it = things.erase(it);
		else window.draw(**it);
	}
}

//NEEDS WORK
void checkCollision(vector<Attacker*> &attackers, vector<Bullet*> &bullets) {
	if (bullets.empty()) return;
	for (auto bIt =bullets.begin() ; bIt != bullets.end(); bIt++) {
		if (attackers.empty()) return;
		for (auto aIt =attackers.begin() ; aIt != attackers.end(); aIt++) {
			if ((*bIt)->getGlobalBounds().intersects((*aIt)->getGlobalBounds())) {
				(*bIt)->hurt(*(*aIt));
				bullets.erase(bIt);
				if ((*aIt)->getHealth() == 0) attackers.erase(aIt);
				if (bullets.empty()) return;
				if (attackers.empty()) return;
			}
			break;
		}
	}
}

/*


for (int i = 0; i < attackers.size(); i++)
            {
                tempattackersPtr = atks[i];
                for (int i = 0; i < bulletList.size(); i++)
                {
                    if (tempattackersPtr[i].getSp()->getGlobalBounds().intersects(bulletList[i].getGlobalBounds()))
                        cat.hurt(bullet); // Does all the calcs
                }

                if (tempattackersPTR hp !0 // !dead)
                {
                    for (int i = 0; i < bulletList.size(); i++)
                    {
                        if (tempattackersPtr[i].getSp()->getGlobalBounds().intersects(bulletList[i].getGlobalBounds()))
                            tower.hurt(bullet); // Does all the calcs
                    }
                }
            }*/

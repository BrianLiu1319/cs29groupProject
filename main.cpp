/********************
 *  Deniz Erisgen
 *  Group Project
 *  Compiler:GCC
********************/
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Collider.hpp"

using namespace sf;
using std::cout;
using std::vector;
using std::endl;

void gameClock(RenderWindow &window, vector<Collider*> &things);

void addBullet(RenderWindow &window, vector<Bullet*> &things);

void addAttacker(RenderWindow &window, vector<Attacker*> &attackers);

void checkCollision(vector<Attacker*> &attackers, vector<Bullet*> &bullets);

int main() {
	srand(time(nullptr));
	RenderWindow window(VideoMode(1280, 720), "DogsnCats", Style::Close | Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	Bullet bulletzz = Bullet();
	Attacker cAttacker = Attacker();
	bulletzz.setPosition((window.getSize().x / 5), (window.getSize().y / 2));
	bulletzz.scale(0.4, 0.4);
	cAttacker.setPosition((4 * window.getSize().x / 5), (window.getSize().y / 2));
	vector<Bullet*> allBullets;
	vector<Attacker*> allAttackers;
	allBullets.push_back(&bulletzz);
	allAttackers.push_back(&cAttacker);
	vector<Collider*> some;
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
						addAttacker(window, allAttackers);
					else if (Keyboard::isKeyPressed(Keyboard::C)) {
						addBullet(window, allBullets);
					} else if (Keyboard::isKeyPressed(Keyboard::Right))
						bulletzz.move(1.0f, 0.0f);
					if (Keyboard::isKeyPressed(Keyboard::Left))
						bulletzz.move(-1.0f, 0.0f);
					if (Keyboard::isKeyPressed(Keyboard::Up))
						bulletzz.move(0.0f, -1.0f);
					if (Keyboard::isKeyPressed(Keyboard::Down))
						bulletzz.move(0.0f, 1.0f);
					break;
				default:;
			}
		}
		window.clear();
		checkCollision(allAttackers, allBullets);
		gameClock(window, reinterpret_cast<vector<class Collider*> &> (allAttackers));
		gameClock(window, reinterpret_cast<vector<class Collider*> &> (allBullets));
//		some.insert(some.end(),allAttackers.begin(),allAttackers.end());
//		some.insert(some.end(),allBullets.begin(),allBullets.end());
		window.display();
		for (auto item : allAttackers) {
			cout << "atackers = "<< item << endl;
		}
		for (auto item : allBullets) {
			cout << "Bullets = "<< item << endl;
		}
	}
	return 0;
}


void gameClock(RenderWindow &window, vector<Collider*> &things) {

	for (auto it = things.begin() ; it != things.end() ; it++) {
		if (*it == nullptr) return;
		(*it)->updateObject();
		if ((*it)->getPosition().x > 2000 || (*it)->getPosition().x < -100) {
			it = things.erase(it);
		} else window.draw(**it);
	}
}





void checkCollision(vector<Attacker*> &attackers, vector<Bullet*> &bullets) {
	for (auto bIt =bullets.begin() ; bIt != bullets.end(); bIt++) {
		if (attackers.empty()) return;
		for (auto att : attackers) {
			if ((*bIt)->getGlobalBounds().intersects(att->getGlobalBounds())) {
				(*bIt)->hurt(*att);
				bullets.erase(bIt);
				if (bullets.empty()) return;
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

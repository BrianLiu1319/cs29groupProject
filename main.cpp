/********************
 *  Deniz Erisgen
 *  Group Project
 *  Compiler:GCC
********************/
#include "SFML/Graphics.hpp"
#include "SFML/System/Thread.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Collider.hpp"

static const std::string bulSpritePath = ResourcePath + "sprites/bul.png";
static const std::string catSpritePath = ResourcePath + "sprites/cat1.png";
using namespace sf;
using std::cout;
using std::vector;
using std::endl;

void gameClock(RenderWindow &window, vector<Collider*> &things);

void addBullet(RenderWindow &window, vector<Bullet*> &things);

void addAttacker(RenderWindow &window, vector<Attacker*> &attackers);

void checkCollision(vector<Attacker*> &attackers, vector<Bullet*> &bullets);

int main() {
	srand(time(NULL));
	RenderWindow window(VideoMode(1280, 720), "DogsnCats", Style::Close | Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	Bullet bulletzz = Bullet(bulSpritePath);
	Attacker cAttacker = Attacker(catSpritePath);
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
	// all goes in here
/*	for (vector<Player>::iterator it=allPlayers.begin();
                              it!=allPlayers.end();
                              *//*it++*//*) <----------- I commented it.
{

   if(it->getpMoney()<=0)
      it = allPlayers.erase(it);
  else
      ++it;
 }*/
	for (auto it = things.begin() ; it != things.end() ; it++) {
		(*it)->updateObject();

		if ((*it)->getPosition().x > 2000 ) {
			it = things.erase(it);
			break;
		} else window.draw(**it);
	}
}

void addBullet(RenderWindow &window, vector<Bullet*> &bullets) {
	auto* temp = new Bullet(bulSpritePath);
	temp->setPosition((window.getSize().x / 5), (window.getSize().y / 2));
	temp->scale(0.4, 0.4);
	bullets.push_back(temp);
}

void addAttacker(RenderWindow &window, vector<Attacker*> &attackers) {
	auto* temp = new Attacker(catSpritePath);
	temp->setPosition((4 * window.getSize().x / 5), (window.getSize().y / 2));
//	temp->scale(0.4, 0.4);
	attackers.push_back(temp);
}

void checkCollision(vector<Attacker*> &attackers, vector<Bullet*> &bullets) {
	for (auto bIt =bullets.begin() ; bIt != bullets.end(); bIt++) {
		for (auto att : attackers) {
			if ((*bIt)->getGlobalBounds().intersects(att->getGlobalBounds())) {
				(*bIt)->hurt(*att);
				bIt = bullets.erase(bIt);
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

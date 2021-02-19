#include "bullet.h"

#include<windows.h>

bullet::bullet() {}
bullet::bullet(Tower aTower, int aSpeed)
{
	string path = "bullet.jpg";
	parentTower = aTower;
	damage = parentTower.getDamage();
	speed = aSpeed;
	position = parentTower.getPosition();
	spBullet = new CircleShape();
	spBullet->setPosition(position.x,position.y);
	spBullet->setRadius(15);
	//spBullet.setScale(1, 0.2);
	spBullet->setFillColor(Color(100, 250, 50));
	
}

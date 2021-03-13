#include "Inventory.hpp"

Inventory::Inventory(Vector2f pt, int co, const Texture &texture) {
	invSprite.setTexture(texture);
	invSprite.setPosition(pt);
	contain = co;
	invSprite.setScale(Vector2f(0.15, 0.15));
}
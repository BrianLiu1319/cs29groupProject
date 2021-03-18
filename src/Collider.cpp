#include "Collider.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
using namespace DIR;

ostream &operator<<(ostream &os, const Collider &collider) {
  os << collider.typeName() << " :"
     << " health: " << collider.health << " speed: " << collider.speed
     << " Origin: X:" << collider.getOrigin().x
     << " Y:" << collider.getOrigin().y;
  return os;
}

Collider::Collider(const string &textureFileName, DIRECTION direction,
                   Vector2f positionOfObj, int objHealth, float objSpeed) {
  speed = objSpeed;
  health = objHealth;
  if (!(textureOfObject.loadFromFile(textureFileName)))
    cerr << "Can not load texture file " << endl;
  setTexture(textureOfObject);

  Vector2f origin(getGlobalBounds().width / 2.0f,
                  getGlobalBounds().height / 2.0f);
  setOrigin(origin);

  defaultDirection = direction;
  setPosition(positionOfObj.x, positionOfObj.y);
}

Collider::Collider(const Texture &textureTemp, DIRECTION direction,
                   Vector2f positionOfObj, int objHealth, float objSpeed) {
  speed = objSpeed;
  health = objHealth;
  setTexture(textureTemp);

  Vector2f origin(getGlobalBounds().width / 2.0f,
                  getGlobalBounds().height / 2.0f);
  setOrigin(origin);
  defaultDirection = direction;
  setPosition(positionOfObj.x, positionOfObj.y);
}

/*
Return the type of object
CODE USED FROM JOE BENTLEY
*/
string Collider::typeName() const {
  string shapeName = typeid(*this).name();
#ifdef _MSC_VER // for MS Visual Studio
  shapeName = shapeName.substr(6);
#else // for other compilers
  shapeName = shapeName.substr(shapeName.find_first_not_of("0123456789"));
#endif
  return shapeName;
}

/*
Allows automatic movement on objects
*/
void Collider::autoTravel(DIRECTION direction) {
  if (direction == DIRECTION::RIGHT)
    this->move(((0.1f) * speed), 0.0f);
  else if (direction == DIRECTION::LEFT)
    this->move(((-0.1f) * speed), 0.0f);
}

/*
Subtracts health from anything that collides
*/
void Collider::hurt(Collider &other) {
  cout << typeName() << "OUCH" << endl;
  cout << "Health Before :" << other.health << endl;
  other.health -= health;
  cout << "Health After :" << other.health << endl;
}

/*
update Collider direction
*/
void Collider::updateObject() {
  if (defaultDirection == DIRECTION::LEFT)
    autoTravel(DIR::DIRECTION::LEFT);
  else if (defaultDirection == DIRECTION::RIGHT)
    autoTravel(DIR::DIRECTION::RIGHT);
}

/*
Sets SFX of bullet
*/
void Bullet::setSfx() {
  try {
    if (!bulletSfxBuffer.loadFromFile(bulletSfxFile)) {
      throw bulletSfxFile;
    }
    bulletSfx.setBuffer(bulletSfxBuffer);
    bulletSfx.setVolume(10.0f);
  } catch (const std::string &fileName) {
    std::cerr << "Unable to open the file " << fileName << std::endl;
    std::cerr << "Location: HowToPlay" << std::endl;
    exit(1);
  }
}

#include "Meteor.h"

Meteor::Meteor() 
{
	textureObject.loadFromFile("image\\asteroid.png");
	SpaceObject.setTexture(textureObject);
	SpaceObject.setTextureRect(IntRect(262, 325, 55, 50));
	restart();
}

Meteor::~Meteor()
{

}

void Meteor::draw(RenderWindow& window) {
	window.draw(SpaceObject);
}

void Meteor::move(float& time) {
	SpaceObject.move(static_cast<float>(-0.5 * time), 0);
	if (SpaceObject.getPosition().x < -60) restart();
}

void Meteor::animation() {
	if (st > 0) {
		SpaceObject.setTextureRect(IntRect(xsp[ix], ysp[iy], 50, 45));
		ix += st;
		if (ix > 4) { ix = 0; iy++; if (iy > 5) iy = 0; }
	}
}

bool Meteor::collision(FloatRect object) {
	if (SpaceObject.getGlobalBounds().intersects(object)) return true;

	return false;
}

void Meteor::restart()
{
	float s = static_cast<float>((rand() % 13 + 5) / 10);
	float x = static_cast<float>(rand() % 1280 + 1280);
	float y = static_cast<float>(rand() % 540 + 130);

	SpaceObject.setPosition(Vector2f(x, y));
	SpaceObject.setScale(s, s);
	ix = rand() % 4;
	iy = rand() % 5;
	st = rand() % 2;
}

FloatRect Meteor::getMeteorBouds() {
	return SpaceObject.getGlobalBounds();
}
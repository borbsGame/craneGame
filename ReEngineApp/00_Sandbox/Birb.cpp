#include "Birb.h"


Birb::Birb(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Birb";
}


Birb::~Birb()
{
}

void Birb::update() {
	if (isFalling) {
		position.y -= .05f;
	}
}

bool Birb::getIsHeld() {
	return isHeld;
}
bool Birb::getIsFalling() {
	return isFalling;
}

void Birb::setIsHeld(bool isHeld) {
	this->isHeld = isHeld;
}
void Birb::setIsFalling(bool isFalling) {
	this->isFalling = isFalling;
}

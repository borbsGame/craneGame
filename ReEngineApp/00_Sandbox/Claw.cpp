#include "Claw.h"



Claw::Claw(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Claw";
}

void Claw::update()
{
	if (isHolding) {
		heldBirb->setPosition(this->getPosition());
	}
}

Claw::~Claw()
{
}

Birb* Claw::getHeldBirb() {
	return heldBirb;
}
bool Claw::getIsHolding() {
	return isHolding;
}

void Claw::setHeldBirb(Birb* heldBirb) {
	this->heldBirb = heldBirb;
}
void Claw::setIsHolding(bool isHolding) {
	this->isHolding = isHolding;
}

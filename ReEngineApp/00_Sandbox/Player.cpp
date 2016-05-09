#include "Player.h"



Player::Player(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Player";
	std::cout << boundingObject->GetRadius();
	SetGravityAffected(false);
}


Player::~Player()
{
}

void Player::update(float a_fDeltaTime) {
	Entity::update(a_fDeltaTime);
}

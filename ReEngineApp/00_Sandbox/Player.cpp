#include "Player.h"



Player::Player(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Player";
	std::cout << boundingObject->GetRadius();
}


Player::~Player()
{
}

void Player::update(float a_fDeltaTime) {

}

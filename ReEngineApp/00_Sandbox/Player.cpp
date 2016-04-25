#include "Player.h"



Player::Player(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Player";
	scale = vector3(0.15f, 0.1f, 0.1f);
	std::cout << boundingObject->GetRadius();
}


Player::~Player()
{
}

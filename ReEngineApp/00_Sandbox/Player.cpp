#include "Player.h"



Player::Player(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Player";
}


Player::~Player()
{
}

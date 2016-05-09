#include "Player.h"



Player::Player(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Player";
	std::cout << boundingObject->GetRadius();
	SetGravityAffected(false);

	score = 0;
	loss = 0;
	gameOver = false;
}


Player::~Player()
{
}

void Player::update(float a_fDeltaTime) {
	Entity::update(a_fDeltaTime);
}

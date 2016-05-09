#include "Hawk.h"



Hawk::Hawk(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Hawk";
	SetForce(vector3(2.0f, 0.0f, 0.0f));
	SetGravityAffected(false);
}


Hawk::~Hawk()
{
}

void Hawk::update(float a_fDeltaTime) {
	//Move from side to side
	if (position.x > 6.5)
	{
		SetForce(vector3(-2.0f, 0.0f, 0.0f));
		facingRight = false;
	}
	else if (position.x < -6.5)
	{
		SetForce(vector3(2.0f, 0.0f, 0.0f));
		facingRight = true;
	}

	Entity::update(a_fDeltaTime);
}

float Hawk::getSpeed() {
	return hawkspeed;
}
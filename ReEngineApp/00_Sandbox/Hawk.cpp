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
	if (position.x > 6)
	{
		SetForce(vector3(-2.0f, 0.0f, 0.0f));
	}
	else if (position.x < -6)
	{
		SetForce(vector3(2.0f, 0.0f, 0.0f));
	}

	Entity::update(a_fDeltaTime);
}

float Hawk::getSpeed() {
	return hawkspeed;
}
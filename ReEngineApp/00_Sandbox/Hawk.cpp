#include "Hawk.h"



Hawk::Hawk(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Hawk";
}


Hawk::~Hawk()
{
}

void Hawk::update(float a_fDeltaTime) {
	//Move from side to side
	if (position.x > 450)
	{
		SetVelocity(vector3(1.0f, 0.0f, 0.0f));
	}
	else if (position.x < -450)
	{
		SetVelocity(vector3(-1.0f, 0.0f, 0.0f));
	}

	Entity::update(a_fDeltaTime);
}

float Hawk::getSpeed() {
	return hawkspeed;
}
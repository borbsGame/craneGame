#include "Hawk.h"



Hawk::Hawk(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Hawk";
	SetVelocity(vector3(1.0f, 0.0f, 0.0f));
}


Hawk::~Hawk()
{
}

void Hawk::update() {
	//Move from side to side
	if (position.x > 450)
	{
		SetVelocity(vector3(-1.0f, 0.0f, 0.0f));
	}
	else if (position.x < -450)
	{
		SetVelocity(vector3(1.0f, 0.0f, 0.0f));
	}
}

float Hawk::getSpeed() {
	return hawkspeed;
}
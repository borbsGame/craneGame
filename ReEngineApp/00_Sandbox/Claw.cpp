#include "Claw.h"



Claw::Claw(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Claw";
}

void Claw::update()
{

}

Claw::~Claw()
{
}

#include "Hawk.h"



Hawk::Hawk(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Hawk";
}


Hawk::~Hawk()
{
}

void Hawk::update() {
	//Move from side to side
}

#include "Birb.h"



Birb::Birb(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Birb";
}


Birb::~Birb()
{
}

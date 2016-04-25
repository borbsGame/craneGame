#ifndef __BIRB_H_
#define __BIRB_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
class Birb :
	public Entity
{
public:
	Birb(std::string renderID, MeshManagerSingleton* meshMngr);
	~Birb();
};
#endif //__BIRB_H_
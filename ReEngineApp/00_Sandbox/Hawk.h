#ifndef __HAWK_H_
#define __HAWK_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
class Hawk :
	public Entity
{
public:
	Hawk(std::string renderID, MeshManagerSingleton* meshMngr);
	~Hawk();
};
#endif //__HAWK_H_

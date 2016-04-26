#ifndef __CLAW_H_
#define __CLAW_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
class Claw :
	public Entity
{
public:
	Claw(std::string renderID, MeshManagerSingleton* meshMngr);
	~Claw();

	void update();
};
#endif //__CLAW_H_


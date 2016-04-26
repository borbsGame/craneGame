#ifndef __CLAW_H_
#define __CLAW_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include"Birb.h"
class Claw :
	public Entity
{
	Birb* heldBirb;
	bool isHolding;

public:
	Claw(std::string renderID, MeshManagerSingleton* meshMngr);
	~Claw();

	void update();

	Birb* getHeldBirb();
	bool getIsHolding();

	void setHeldBirb(Birb* heldBirb);
	void setIsHolding(bool isHolding);
};
#endif //__CLAW_H_


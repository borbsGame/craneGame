#ifndef __BIRB_H_
#define __BIRB_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
class Birb :
	public Entity
{
	bool isHeld;
	bool isFalling;
public:
	Birb(std::string renderID, MeshManagerSingleton* meshMngr);
	~Birb();

	void update();

	bool getIsHeld();
	bool getIsFalling();

	void setIsHeld(bool isHeld);
	void setIsFalling(bool isFalling);
};
#endif //__BIRB_H_
#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include"Birb.h"
class Player:
	public Entity
{
	Birb* heldBirb;
	bool isHolding;
public:
	vector3 bodyPosition;
	vector3 legPosition;

	Player(std::string renderID, MeshManagerSingleton* meshMngr);
	~Player();

	void update();

	Birb* getHeldBirb();
	bool getIsHolding();

	void setHeldBirb(Birb* heldBirb);
	void setIsHolding(bool isHolding);
};
#endif //__PLAYER_H_


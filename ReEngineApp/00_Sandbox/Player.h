#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
class Player:
	public Entity
{
public:
	vector3 bodyPosition;
	vector3 legPosition;

	Player(std::string renderID, MeshManagerSingleton* meshMngr);
	~Player();
};
#endif //__PLAYER_H_


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

	int score;
	int loss;
	bool gameOver;

	Player(std::string renderID, MeshManagerSingleton* meshMngr);
	~Player();

	void update(float a_fDeltaTime);


};
#endif //__PLAYER_H_


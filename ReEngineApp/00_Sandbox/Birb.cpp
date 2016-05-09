#include "Birb.h"


Birb::Birb(std::string renderID, MeshManagerSingleton* meshMngr) : Entity(renderID, meshMngr)
{
	this->type = "Birb";
	//SetGravityAffected(false);
	m_fFriction = 0.02f;

	//ApplyForce(vector3(0.0f, 2.0f, 0.0f));
}


Birb::~Birb()
{
}

void Birb::update(float a_fDeltaTime) {
	

	/*Karen's Notes
		Get the number of entries in EntityManager CHECK
		Go through the list and check if it's a Birb 
		If Birb
			set forces...
			if setFalling is true
			getOriginalheight and then do that shit below 

			s = ut + at^2/2. s is distance, u is the initial speed (in this case zero), t is time, and a is acceleration 

			Reference https://www.physicsforums.com/threads/bouncing-ball-equation.403229/
	*/
	if (isFalling) {
		SetGravityAffected(true);
		if (position.y < -2.0f){
			if (!hasBounced) {
				ApplyForce(vector3(0.0f, GetVelocity().y * -150.0f, 0.0f));
				hasBounced = true;
			}
			else {
				SetGravityAffected(false);
				SetForce(vector3(0.0f));
				SetVelocity(vector3(0.0f));
				isFalling = false;
				hasBounced = false;
			}
		}
		
	}
	else {
		SetGravityAffected(false);
	}
	
	Entity::update(a_fDeltaTime);
}

bool Birb::getIsHeld() {
	return isHeld;
}
bool Birb::getIsFalling() {
	return isFalling;
}

void Birb::setIsHeld(bool isHeld) {
	this->isHeld = isHeld;
}
void Birb::setIsFalling(bool isFalling) {
	this->isFalling = isFalling;
}

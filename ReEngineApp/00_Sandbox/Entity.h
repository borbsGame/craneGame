#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "RE\ReEng.h"
#include "BoundingObject.h"
class Entity
{
protected:
	std::string renderID;
	vector3 scale;
	vector3 position;
	glm::quat rotation;

	std::string type;

	BoundingObject* boundingObject;

	//Alberto's
	bool m_bGravityAffected = true; //flag for gravity
	vector3 m_v3Position = ZERO_V3; //Position of the Entity
	vector3 m_v3PositionPrevious = ZERO_V3; //Position of the Entity

	vector3 m_v3Velocity = ZERO_V3; //Velocity of the Entity
	vector3 m_v3Force = ZERO_V3; //Acceleration of the Entity

	float m_fFriction = 0.0f; //Friction factor of the entity between 0 and 1
	float m_fMass = 1.0f;	//Mass of the Entity
	float m_fMaxVelocity = 1.0f; //Limit of the acceleration of the entity

public:
	Entity(std::string renderID, MeshManagerSingleton* meshMngr);
	~Entity();

	virtual void update() = 0;

	std::string getRenderID();
	std::string getType();
	matrix4 getModelMatrix();


	BoundingObject* getBO();
	vector3 getPosition();
	vector3 getScale();
	glm::quat getRotation();

	void setPosition(vector3 position);
	void setScale(vector3 scale);
	void setRotation(glm::quat rotation);

	int test = 0;

	//Alberto's
	void SetMaxVelocity(float a_fMaxVelocity);
	/*
	USAGE: Accessor of friction
	ARGUMENTS:
	--- float a_fFriction -> friction input
	OUTPUT: ---
	*/
	void SetFriction(float a_fFriction);
	/*
	USAGE: Accessor of mass
	ARGUMENTS: float a_fMass -> mass input
	OUTPUT: ---
	*/
	void SetMass(float a_fMass);
	/*
	USAGE: Accessor of mass
	ARGUMENTS: ---
	OUTPUT: float -> mass
	*/
	float GetMass(void);
	/*
	USAGE: Accessor of gravity
	ARGUMENTS:
	--- bool a_bGravity -> Gravity flag
	OUTPUT: ---
	*/
	void SetGravityAffected(bool a_bGravity);
	/*
	USAGE: Accessor of gravity
	ARGUMENTS: ---
	OUTPUT: bool -> gravity flag
	*/
	bool GetGravityAffected(void);
	/*
	USAGE: Accessor of Position
	ARGUMENTS:
	--- vector3 a_v3Position -> position input
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position);
	/*
	USAGE: Returns the position the object was last call
	ARGUMENTS: ---
	OUTPUT: vector3 -> Last known position
	*/
	vector3 GetLastPosition(void);
	/*
	USAGE: Accessor of Position
	ARGUMENTS: ---
	OUTPUT:  vector3 -> position
	*/
	vector3 GetPosition(void);
	/*
	USAGE: Accessor of velocity
	ARGUMENTS:
	--- vector3 a_v3Velocity -> velocity input
	OUTPUT: ---
	*/
	void SetVelocity(vector3 a_v3Velocity);
	/*
	USAGE: Applies a force into the entity
	ARGUMENTS: vector3 a_v3Force -> input force
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force);
	/*
	USAGE: Accessor of force
	ARGUMENTS: ---
	OUTPUT: vector3 -> acceleration of entity
	*/
	vector3 GetForce(void);
	/*
	USAGE: Accessor of force
	ARGUMENTS: vector3 -> acceleration of entity
	OUTPUT: ---
	*/
	void SetForce(vector3 a_v3Force);
	/*
	USAGE: Accessor of Velocity
	ARGUMENTS: ---
	OUTPUT: vector3 -> velocity of entity
	*/
	vector3 GetVelocity(void);
	/*
	USAGE: Adds gravity on the entity based on the time difference
	ARGUMENTS:
	--- float a_fDeltaTime -> Time difference between calls
	OUTPUT: ---
	*/
	void ApplyGravity(float a_fDeltaTime);
	/*
	USAGE: Accessor of name
	ARGUMENTS: ---
	OUTPUT: String -> name of entity
	*/
};
#endif //__ENTITY_H_

#ifndef __ENTITYMANAGER_H_
#define __ENTITYMANAGER_H_

#include <vector>
#include "BoundingObject.h"
#include "Entity.h"

#include "Player.h"
#include "Birb.h"
#include "Hawk.h"
#include "Claw.h"

class EntityManager
{
	static EntityManager* instance;
	static MeshManagerSingleton* mesh;
	uint m_nEntityCount = 0;
	std::map<String, uint> m_map;//Map relating the mesh and the index

public:
	std::vector<Entity*> entitiesList;

	void Init();

	static EntityManager* GetInstance();

	static void ReleaseInstance();

	void addEntity(Entity* entity);


	void createBoundingObject(std::vector<vector3> vertices);


	void checkCollisions();


	void collide(Entity* entityOne, Entity* entityTwo);


	void setMeshManager(MeshManagerSingleton* ms);

	int getNumEntities();
	Entity* getEntity(int index);


	void BOVisable(BoundingObject* boundObject, bool vis);
	void setBOColor(BoundingObject* boundObject, vector3 color);
	void renderSpecificBO(BoundingObject* boundObject);
	void renderAllBO();

	void setModelMatricies();
	void updateEntities();

	//Alberto's
	int GetIndex(String a_sEntity);

	void SetMass(float a_fMass, String a_sEntity);
	/*
	USAGE: Accessor of friction
	ARGUMENTS:
	--- float a_fFriction -> friction input
	OUTPUT: ---
	*/
	void SetFriction(float a_fFriction, String a_sEntity);
	/*
	USAGE: Accessor of Maximum velocity
	ARGUMENTS:
	--- float a_fMaxVelocity -> Max Acceleration input
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetMaxVelocity(float a_fMaxVelocity, String a_sEntity);
	/*
	USAGE: Accessor of Position
	ARGUMENTS:
	--- vector3 a_v3Position -> position input
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position, String a_sEntity);
	/*
	USAGE: Accessor of velocity
	ARGUMENTS:
	--- vector3 a_v3Velocity -> velocity input
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetVelocity(vector3 a_v3Velocity, String a_sEntity);
	/*
	USAGE: Accessor of gravity
	ARGUMENTS:
	--- bool a_bGravity -> Gravity flag
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetGravityAffected(bool a_bGravity, String a_sEntity);
	/*
	USAGE: Applies a force into the entity
	ARGUMENTS:
	--- vector3 a_v3Force -> input force
	--- String a_sEntity -> entity id
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force, String a_sEntity);
	/*
	USAGE: Updates all the Entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/


private:
	EntityManager() {};
	EntityManager(EntityManager const& other) {};
	EntityManager& operator=(EntityManager const& other) {};
	~EntityManager() { Release(); }
	void Release();

};

#endif //__ENTITYMANAGER_H_

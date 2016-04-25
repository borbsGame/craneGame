#ifndef __ENTITYMANAGER_H_
#define __ENTITYMANAGER_H_

#include <vector>
#include "BoundingObject.h"
#include "Entity.h"

class EntityManager
{
	static EntityManager* instance;
	static MeshManagerSingleton* mesh;

public:
	std::vector<Entity*> entitiesList;

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


private:
	EntityManager() {};
	EntityManager(EntityManager const& other) {};
	EntityManager& operator=(EntityManager const& other) {};
	~EntityManager() { Release(); }
	void Release();

};

#endif //__ENTITYMANAGER_H_

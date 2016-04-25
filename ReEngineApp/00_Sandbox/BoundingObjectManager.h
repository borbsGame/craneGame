#ifndef __BOUNDINGOBJECTMANAGER_H_
#define __BOUNDINGOBJECTMANAGER_H_

#include <vector>
#include "BoundingObject.h"

class BoundingObjectManager
{
	static BoundingObjectManager* instance;
	static MeshManagerSingleton* mesh;

public:
	std::vector<BoundingObject*> boundObj;

	static BoundingObjectManager* GetInstance();

	static void ReleaseInstance();


	BoundingObject* createBoundingObject(String model);

	void addBoundingObject(BoundingObject* boundObject);


	void createBoundingObject(std::vector<vector3> vertices);


	void checkCollisions();


	void collide(BoundingObject* bObjOne, BoundingObject* bObjTwo);


	void setMeshManager(MeshManagerSingleton* ms);

	int getNumBoundObjects();
	BoundingObject* getBoundObject(int index);


	void boxVisable(BoundingObject* boundObject, bool vis);
	void setColor(BoundingObject* boundObject, vector3 color);
	void renderSpecific(BoundingObject* boundObject);
	void renderAll();


private:
	BoundingObjectManager() {};
	BoundingObjectManager(BoundingObjectManager const& other) {};
	BoundingObjectManager& operator=(BoundingObjectManager const& other) {};
	~BoundingObjectManager() { Release(); }
	void Release();

};

#endif //__BOUNDINGOBJECTMANAGER_H_

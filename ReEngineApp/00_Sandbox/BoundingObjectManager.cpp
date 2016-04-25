#include "BoundingObjectManager.h"

BoundingObjectManager* BoundingObjectManager::instance;
MeshManagerSingleton* BoundingObjectManager::mesh;

BoundingObjectManager* BoundingObjectManager::GetInstance()
{
	if (instance == nullptr)
		instance = new BoundingObjectManager();
	return instance;
}
void BoundingObjectManager::ReleaseInstance()
{
	if (instance != nullptr)
	{

		delete instance;
		instance = nullptr;
	}
}

BoundingObject* BoundingObjectManager::createBoundingObject(String model) {
	return new BoundingObject(mesh->GetVertexList(model));
}

void BoundingObjectManager::addBoundingObject(BoundingObject* boundObject)
{
	boundObj.push_back(boundObject);
}

void BoundingObjectManager::createBoundingObject(std::vector<vector3> vertices)
{
	boundObj.push_back(new BoundingObject(vertices));
}

void BoundingObjectManager::checkCollisions()
{
	/*int index = 0;
	MyBoundingObjectClass temp1 = boundObj.at(index);

	int count = 1;
	bool notDone = true;

	while (index < getNumBoundObjects())
	{
	MyBoundingObjectClass* temp2 = &getBoundObject(count);

	if (temp1.IsColliding(temp2))
	{
	collide(temp1, getBoundObject(count));
	}
	else
	{
	setColor(temp1, REGREEN);
	if (count == getNumBoundObjects()) { count = 0; index++; }
	else { count++; }

	}

	}*/
	int count = 1;
	int numofBO = getNumBoundObjects();
	static int index = 0;

	for (int i = 1; i < numofBO; i++)
	{
		BoundingObject* temp1 = boundObj.at(index);
		BoundingObject* temp2 = getBoundObject(i);

		if (temp1->IsColliding(temp2))
		{
			collide(temp1, getBoundObject(i));
		}
		else if (count == 0)
		{
			index++;
		}
		else
		{
			setColor(temp1, REGREEN);
			setColor(temp2, REGREEN);
			count++;
			count %= numofBO;
		}
	}

	if (index == numofBO)
	{
		index = 0;
	}


}

void BoundingObjectManager::collide(BoundingObject* bObjOne, BoundingObject* bObjTwo)
{
	setColor(bObjOne, RERED);
	setColor(bObjTwo, RERED);
}

void BoundingObjectManager::setMeshManager(MeshManagerSingleton* ms) {
	mesh = ms;
}

int BoundingObjectManager::getNumBoundObjects() {
	return boundObj.size();
}

BoundingObject* BoundingObjectManager::getBoundObject(int index)
{
	if (index < getNumBoundObjects())
		return boundObj[index];
	else
		return boundObj[0];
}

void BoundingObjectManager::boxVisable(BoundingObject* boundObject, bool vis) {
	boundObject->setBoxVisibility(vis);
}
void BoundingObjectManager::setColor(BoundingObject* boundObject, vector3 color) {
	boundObject->setColor(color);
}
void BoundingObjectManager::renderSpecific(BoundingObject* boundObject) {
	boundObject->drawBO(mesh);
	boundObject->setBoxVisibility(true);
}
void BoundingObjectManager::renderAll() {
	for each(BoundingObject* bound in boundObj) {
		bound->drawBO(mesh);
		bound->setBoxVisibility(true);
	}
}


void BoundingObjectManager::Release()
{
	for each(BoundingObject* bound in boundObj) {
		delete bound;
	}
	boundObj.clear();
}

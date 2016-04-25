#include "EntityManager.h"

EntityManager* EntityManager::instance;
MeshManagerSingleton* EntityManager::mesh;

EntityManager* EntityManager::GetInstance()
{
	if (instance == nullptr)
		instance = new EntityManager();
	return instance;
}
void EntityManager::ReleaseInstance()
{
	if (instance != nullptr)
	{

		delete instance;
		instance = nullptr;
	}
}

void EntityManager::addEntity(Entity* entity)
{
	entitiesList.push_back(entity);
}

void EntityManager::createBoundingObject(std::vector<vector3> vertices)
{
	//boundObj.push_back(new BoundingObject(vertices));
}

void EntityManager::checkCollisions()
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
	int numofBO = getNumEntities();
	static int index = 0;

	for (int i = 1; i < numofBO; i++)
	{
		Entity* temp1 = entitiesList.at(index);
		Entity* temp2 = getEntity(i);

		if (temp1->getBO()->IsColliding(temp2->getBO()))
		{
			collide(temp1, temp2);
		}
		else if (count == 0)
		{
			index++;
		}
		else
		{
			count++;
			count %= numofBO;
		}
	}

	if (index == numofBO)
	{
		index = 0;
	}


}

void EntityManager::collide(Entity* entityOne, Entity* entityTwo)
{
	if (entityOne->getType() == "Player") {

	}
	else if (entityOne->getType() == "Birb") {
		
	}
	else if (entityOne->getType() == "Hawk") {

	}
	else if (entityOne->getType() == "Nest") {

	}
}

void EntityManager::setMeshManager(MeshManagerSingleton* ms) {
	mesh = ms;
}

int EntityManager::getNumEntities() {
	return entitiesList.size();
}

Entity* EntityManager::getEntity(int index)
{
	if (index < getNumEntities())
		return entitiesList[index];
	else
		return entitiesList[0];
}

void EntityManager::BOVisable(BoundingObject* boundObject, bool vis) {
	boundObject->setBoxVisibility(vis);
}
void EntityManager::setBOColor(BoundingObject* boundObject, vector3 color) {
	boundObject->setColor(color);
}
void EntityManager::renderSpecificBO(BoundingObject* boundObject) {
	boundObject->drawBO(mesh);
	boundObject->setBoxVisibility(true);
}
void EntityManager::renderAllBO() {
	for each(Entity* entity in entitiesList) {
		entity->getBO()->drawBO(mesh);
		entity->getBO()->setBoxVisibility(true);
	}
}

void EntityManager::setModelMatricies(){
	for each(Entity* entity in entitiesList) {
		mesh->SetModelMatrix(entity->getModelMatrix(), entity->getRenderID());
	}
}
void EntityManager::updateEntities() {

}


void EntityManager::Release()
{
	for each(Entity* entity in entitiesList) {
		delete entity;
	}
	entitiesList.clear();
}
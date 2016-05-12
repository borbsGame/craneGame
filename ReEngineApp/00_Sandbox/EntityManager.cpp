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

void EntityManager::Init(void)
{
	m_nEntityCount = 0;
	score = 0;
	loss = 3;
	gameOver = false;
}

void EntityManager::addEntity(Entity* entity)
{
	entitiesList.push_back(entity);

	m_map[entity->getRenderID()] = m_nEntityCount;
	m_nEntityCount++;
}

void EntityManager::createBoundingObject(std::vector<vector3> vertices)
{
	//boundObj.push_back(new BoundingObject(vertices));
}

void EntityManager::checkCollisions()
{
	int count = 1;
	int numofBO = getNumEntities();
	static int index = 0;

	/*for (int i = 0; i < getNumEntities(); i++) {
		for(int j = 0; j < getNumEntities(); j++) {
			if (i != j) {
				Entity* temp1 = getEntity(i);
				Entity* temp2 = getEntity(j);

				if (temp1->getBO()->IsColliding(temp2->getBO()))
				{
					collide(temp1, temp2);
				}
			}
		}
	}*/


}

void EntityManager::collide(Entity* entityOne, Entity* entityTwo)
{
	

	//If checking the collsion of Player and Claw and if it Claw is holding, 
	if (entityOne->getType() == "Player") {
		if (entityTwo->getType() == "Claw") {
			Player* tempPlayer = ((Player*)entityOne);
			Claw* tempClaw = ((Claw*)entityTwo);
			if (tempClaw->getIsHolding()) {
				tempClaw->dropBirb();
				score++;
				tempClaw->getHeldBirb()->setPosition(vector3(1000, 1000, 0));
			}
		}
	}
	else if (entityOne->getType() == "Claw") {
		if (entityTwo->getType() == "Birb") {
			Claw* tempClaw = ((Claw*)entityOne);
			Birb* tempBirb = ((Birb*)entityTwo);
			if (!tempClaw->getIsHolding() && !tempBirb->getIsFalling()) {
				tempClaw->setIsHolding(true);
				tempClaw->setHeldBirb(tempBirb);
				tempBirb->setIsHeld(true);
			}
		}
		else if (entityTwo->getType() == "Hawk") {
			Claw* tempClaw = ((Claw*)entityOne);
			if (tempClaw->getIsHolding()) {
				tempClaw->dropBirb();
				loss--;
			}
		}
		else if (entityTwo->getType() == "Player") {
			Claw* tempClaw = ((Claw*)entityOne);
			if (tempClaw->getIsHolding()) {
				tempClaw->dropBirb();
				score++;
				tempClaw->getHeldBirb()->setPosition(vector3(1000, 1000, 0));
			}
		}
	}
	else if (entityOne->getType() == "Birb") {
		if (entityTwo->getType() == "Claw") {
			Claw* tempClaw = ((Claw*)entityTwo);
			Birb* tempBirb = ((Birb*)entityOne);
			if (!tempClaw->getIsHolding() && !tempBirb->getIsFalling()) {
				tempClaw->setIsHolding(true);
				tempClaw->setHeldBirb(tempBirb);

				tempBirb->setIsHeld(true);

				//entityTwo->setPosition(entityOne->getPosition());
			}

		}
		else if (entityTwo->getType() == "Player") {

		}
	}
	else if (entityOne->getType() == "Hawk") {
		if (entityTwo->getType() == "Claw") {
			Claw* tempClaw = ((Claw*)entityTwo);
			if (tempClaw->getIsHolding()) {
				tempClaw->dropBirb();
				loss--;
			}
		}
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
		//entity->getBO()->drawBO(mesh);
		entity->getBO()->setBoxVisibility(true);
		//entity->getBO()->DisplayReAlligned(mesh);
	}
}

void EntityManager::setModelMatricies(){
	for each(Entity* entity in entitiesList) {
		mesh->SetModelMatrix(entity->getModelMatrix(), entity->getRenderID());

		//Reset BO Model Matrix
		entity->getBO()->SetModelMatrix(mesh->GetModelMatrix(entity->getRenderID()));
	}
}

//Alberto's
int EntityManager::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_map.find(a_sIndex);
	//If not found return -1
	if (var == m_map.end())
		return -1;
	return var->second;//Get the index
}

void EntityManager::SetMass(float a_fMass, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		entitiesList[nIndex]->SetMass(a_fMass);
}
void EntityManager::SetFriction(float a_fFriction, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		entitiesList[nIndex]->SetFriction(a_fFriction);
}
void EntityManager::SetMaxVelocity(float a_fMaxVelocity, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		entitiesList[nIndex]->SetMaxVelocity(a_fMaxVelocity);
}
/*void EntityManager::SetPosition(vector3 a_v3Position, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		entitiesList[nIndex]->SetPosition(a_v3Position);
}*/
void EntityManager::SetVelocity(vector3 a_v3Velocity, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		entitiesList[nIndex]->SetVelocity(a_v3Velocity);
}

void EntityManager::SetGravityAffected(bool a_bGravity, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		entitiesList[nIndex]->SetGravityAffected(a_bGravity);
}
//--- Non Standard Singleton Methods
void EntityManager::ApplyForce(vector3 a_v3Force, String a_sEntity)
{
	int nIndex = GetIndex(a_sEntity);
	if (nIndex >= 0)
	{
		entitiesList[nIndex]->ApplyForce(a_v3Force);
	}
}

void EntityManager::updateEntities() {
	SystemSingleton* m_pSystem = SystemSingleton::GetInstance();
	static int nClock = m_pSystem->AddClock();
	float fDeltaTime = static_cast<float>(m_pSystem->LapClock(nClock));

	for each(Entity* entity in entitiesList) {
		entity->update(fDeltaTime);
		entity->getBO()->setEntity(entity);
	}
}


void EntityManager::Release()
{
	for each(Entity* entity in entitiesList) {
		delete entity;
	}
	entitiesList.clear();
}

uint EntityManager::GetEntityCount(void) { return m_nEntityCount; }

BoundingObject* EntityManager::GetBoundingObject(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	return GetBoundingObject(nIndex);
}
BoundingObject* EntityManager::GetBoundingObject(uint a_nIndex)
{
	if (a_nIndex < m_nEntityCount)
		return entitiesList[a_nIndex]->getBO();
		//return m_lObject[a_nIndex];

	return nullptr;
}

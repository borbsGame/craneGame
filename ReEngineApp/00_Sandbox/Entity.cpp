#include "Entity.h"



Entity::Entity(std::string renderID, MeshManagerSingleton* meshMngr)
{
	this->renderID = renderID;
	boundingObject = new BoundingObject(meshMngr->GetVertexList(renderID));
	
	scale = vector3(1.0f, 1.0f, 0.1f);
	position = vector3(0.0f, 0.0f, 0.0f);
	rotation = glm::angleAxis(0.0f, vector3(0.0f, 1.0f, 0.0f));
}

void Entity::update(float a_fDeltaTime)
{

	//Apply friction
	float fFriction = MapValue(m_fFriction, 0.0f, 1.0f, 1.0f, 0.0f);
	m_v3Force = m_v3Force * fFriction;

	//Apply Gravity
	ApplyGravity(a_fDeltaTime);

	//Calculate the velocity based on acceleration delta time
	vector3 v3Velocity = m_v3Force * a_fDeltaTime;
	//if(m_bGravityAffected)
	//	v3Velocity += vector3(0.0f, -0.9f, 0.0f) * a_fDeltaTime;
	
	//Increase the velocity based on the acceleration
	m_v3Velocity = glm::clamp(v3Velocity, -m_fMaxVelocity, m_fMaxVelocity);
	//Set the position based on the position of this object and the acceleration
	m_v3Position += m_v3Velocity;

	//Transform to the position
	matrix4 m4ToWorld = glm::translate(m_v3Position);


}

Entity::~Entity()
{
	delete this->boundingObject;
}

std::string Entity::getRenderID() {
	return this->renderID;
}
std::string Entity::getType() {
	return this->type;
}
matrix4 Entity::getModelMatrix() {
	return glm::scale(scale) * glm::translate(position) * glm::mat4_cast(rotation);
}
BoundingObject* Entity::getBO() {
	return this->boundingObject;
}

vector3 Entity::getPosition() {
	return this->position;
}
vector3 Entity::getScale() {
	return this->scale;
}
glm::quat Entity::getRotation() {
	return this->rotation;
}

void Entity::setPosition(vector3 position) {
	this->position = position;
}
void Entity::setScale(vector3 scale) {
	this->scale = scale;
}
void Entity::setRotation(glm::quat rotation) {
	this->rotation = rotation;
}

//Alberto's
void Entity::SetVelocity(vector3 a_v3Velocity) { m_v3Velocity = a_v3Velocity; }
void Entity::SetMaxVelocity(float a_fMaxVelocity) { m_fMaxVelocity = a_fMaxVelocity; }
void Entity::SetMass(float a_fMass) { m_fMass = a_fMass; }
void Entity::SetFriction(float a_fFriction) { m_fFriction = a_fFriction; }
void Entity::SetForce(vector3 a_v3Force) { m_v3Force = a_v3Force; }

float Entity::GetMass(void) { return m_fMass; }
vector3 Entity::GetLastPosition(void) { return m_v3PositionPrevious; }
vector3 Entity::GetPosition(void) { return m_v3Position; }
vector3 Entity::GetForce(void) { return m_v3Force; }
vector3 Entity::GetVelocity(void) { return m_v3Velocity; }

void Entity::SetGravityAffected(bool a_bGravity) { m_bGravityAffected = a_bGravity; }
bool Entity::GetGravityAffected(void) { return m_bGravityAffected; }

//---
void Entity::ApplyForce(vector3 a_v3Force)
{
	//force = mass * acceleration
	m_v3Force += a_v3Force / m_fMass;
}
void Entity::ApplyGravity(float a_fDeltaTime)
{
	if (m_bGravityAffected)
		m_v3Force += vector3(0.0f, -9.81f, 0.0f) * a_fDeltaTime;
}

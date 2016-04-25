#include "Entity.h"



Entity::Entity(std::string renderID, MeshManagerSingleton* meshMngr)
{
	this->renderID = renderID;
	boundingObject = new BoundingObject(meshMngr->GetVertexList(renderID));
	
	scale = vector3(1.0f, 1.0f, 0.1f);
	position = vector3(0.0f, 0.0f, 0.0f);
	rotation = glm::angleAxis(0.0f, vector3(0.0f, 1.0f, 0.0f));
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
	//return glm::translate(position) * glm::mat4_cast(rotation);
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

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

public:
	Entity(std::string renderID, MeshManagerSingleton* meshMngr);
	~Entity();

	//virtual void update();

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
};
#endif //__ENTITY_H_

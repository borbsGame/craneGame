#include "BoundingObject.h"

void BoundingObject::Init(void)
{
	m_fRadius = 0.0f;
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
}
void BoundingObject::Swap(BoundingObject& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);

	std::swap(m_fRadius, other.m_fRadius);
}
void BoundingObject::Release(void)
{

}
//The big 3
BoundingObject::BoundingObject(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;
}
BoundingObject::BoundingObject(BoundingObject const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;

	m_fRadius = other.m_fRadius;
}
BoundingObject& BoundingObject::operator=(BoundingObject const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		BoundingObject temp(other);
		Swap(temp);
	}
	return *this;
}
BoundingObject::~BoundingObject() {
	Release();
};

void BoundingObject::drawBO(MeshManagerSingleton* meshMngr) {
	if (m_isVisible) {
		/*if (m_boxVisible) {
			meshMngr->AddCubeToQueue(
				glm::translate(vector3(this->GetCenterGlobal())) *
				glm::scale(vector3(this->GetSize())), this->m_Color, WIRE);
		}
		meshMngr->AddSphereToQueue(
			glm::translate(vector3(this->GetCenterGlobal())) *
			glm::scale(vector3(this->GetRadius()) * 2.0f), this->m_Color, WIRE);*/
	}
}

void BoundingObject::DisplaySphere(MeshManagerSingleton* meshMngr)
{
	meshMngr->AddSphereToQueue(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(vector3(m_fRadius * 2.0f)), m_Color, WIRE);
}
void BoundingObject::DisplayOriented(MeshManagerSingleton* meshMngr)
{
	meshMngr->AddCubeToQueue(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(m_v3HalfWidth * 2.0f), m_Color, WIRE);
}
void BoundingObject::DisplayReAlligned(MeshManagerSingleton* meshMngr)
{
	meshMngr->AddCubeToQueue(glm::translate(IDENTITY_M4, m_v3CenterG) *
		glm::scale(m_v3HalfWidthG * 2.0f), m_Color, WIRE);
}


//Accessors
void BoundingObject::SetModelMatrix(matrix4 a_m4ToWorld) {
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the Object
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		v3Corner[nVertex] = vector3(m_m4ToWorld * vector4(v3Corner[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxG = m_v3MinG = v3Corner[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinG.x > v3Corner[nVertex].x) //If min is larger than current
			m_v3MinG.x = v3Corner[nVertex].x;
		else if (m_v3MaxG.x < v3Corner[nVertex].x)//if max is smaller than current
			m_v3MaxG.x = v3Corner[nVertex].x;

		if (m_v3MinG.y > v3Corner[nVertex].y) //If min is larger than current
			m_v3MinG.y = v3Corner[nVertex].y;
		else if (m_v3MaxG.y < v3Corner[nVertex].y)//if max is smaller than current
			m_v3MaxG.y = v3Corner[nVertex].y;

		if (m_v3MinG.z > v3Corner[nVertex].z) //If min is larger than current
			m_v3MinG.z = v3Corner[nVertex].z;
		else if (m_v3MaxG.z < v3Corner[nVertex].z)//if max is smaller than current
			m_v3MaxG.z = v3Corner[nVertex].z;
	}
	m_v3CenterG = (m_v3MinG + m_v3MaxG) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthG = (m_v3MaxG - m_v3MinG) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterG, m_v3MaxG);
}
vector3 BoundingObject::GetCenterLocal(void) { return m_v3Center; }
vector3 BoundingObject::GetCenterGlobal(void) { return m_v3CenterG; }
vector3 BoundingObject::GetHalfWidth(void) { return m_v3HalfWidth; }
vector3 BoundingObject::GetHalfWidthG(void) { return m_v3HalfWidthG; }
vector3 BoundingObject::GetMin(void) { return m_v3Min; }
vector3 BoundingObject::GetMax(void) { return m_v3Max; }
vector3 BoundingObject::GetMinG(void) { return m_v3MinG; }
vector3 BoundingObject::GetMaxG(void) { return m_v3MaxG; }

float BoundingObject::GetRadius(void) {
	return m_fRadius;
}
matrix4 BoundingObject::GetModelMatrix(void) {
	return m_m4ToWorld;
}
vector3 BoundingObject::GetSize(void) {
	return m_v3Size;
}
void BoundingObject::setColor(vector3 color) {
	this->m_Color = color;
}
bool BoundingObject::getVisibility() {
	return m_isVisible;
}
void BoundingObject::setVisibility(bool isVisible) {
	m_isVisible = isVisible;
}
bool BoundingObject::getBoxVisibility() {
	return m_boxVisible;
}
void BoundingObject::setBoxVisibility(bool isVisible) {
	m_boxVisible = isVisible;
}


bool BoundingObject::IsColliding(BoundingObject* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(GetMin(), 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(GetMax(), 1.0f));

	vector3 v3MinO = vector3(a_pOther->GetModelMatrix() *vector4(a_pOther->GetMin(), 1.0f));
	vector3 v3MaxO = vector3(a_pOther->GetModelMatrix() * vector4(a_pOther->GetMax(), 1.0f));

	/*
	Are they colliding?
	For Objects we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	//first check the bounding sphere, if that is not colliding we can guarantee that there are no collision
	if ((m_fRadius + a_pOther->GetRadius()) < glm::distance(m_v3CenterG, a_pOther->GetCenterGlobal()))
		return false;

	//If the distance was smaller it might be colliding

	bool bColliding = true;

	//Check for X
	if (m_v3MaxG.x < a_pOther->GetMinG().x)
		bColliding = false;
	if (m_v3MinG.x > a_pOther->GetMaxG().x)
		bColliding = false;

	//Check for Y
	if (m_v3MaxG.y < a_pOther->GetMinG().y)
		bColliding = false;
	if (m_v3MinG.y > a_pOther->GetMaxG().y)
		bColliding = false;

	//Check for Z
	if (m_v3MaxG.z < a_pOther->GetMinG().z)
		bColliding = false;
	if (m_v3MinG.z > a_pOther->GetMaxG().z)
		bColliding = false;


	if (bColliding) {
		if (RunSAT(a_pOther)) {
			std::cout << "hey";
		}
		return RunSAT(a_pOther);
	}

	return bColliding;
}

bool BoundingObject::RunSAT(BoundingObject* const a_pOther) {
	float ra, rb;
	matrix3 rot, absRot;
	vector3 myAxes[3];
	vector3 otherAxes[3];
	vector3 myHalfW = this->GetHalfWidth();
	vector3 otherHalfW = a_pOther->GetHalfWidth();

	myAxes[0] = vector3(m_m4ToWorld[0][0], m_m4ToWorld[0][1], m_m4ToWorld[0][2]);
	myAxes[1] = vector3(m_m4ToWorld[1][0], m_m4ToWorld[1][1], m_m4ToWorld[1][2]);
	myAxes[2] = vector3(m_m4ToWorld[2][0], m_m4ToWorld[2][1], m_m4ToWorld[2][2]);


	otherAxes[0] = vector3(a_pOther->m_m4ToWorld[0][0], a_pOther->m_m4ToWorld[0][1], a_pOther->m_m4ToWorld[0][2]);
	otherAxes[1] = vector3(a_pOther->m_m4ToWorld[1][0], a_pOther->m_m4ToWorld[1][1], a_pOther->m_m4ToWorld[1][2]);
	otherAxes[2] = vector3(a_pOther->m_m4ToWorld[2][0], a_pOther->m_m4ToWorld[2][1], a_pOther->m_m4ToWorld[2][2]);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rot[i][j] = glm::dot(myAxes[i], otherAxes[j]);
		}
	}

	vector3 translation = a_pOther->GetCenterGlobal() - this->GetCenterGlobal();
	translation = vector3(glm::dot(translation, myAxes[0]), glm::dot(translation, myAxes[1]), glm::dot(translation, myAxes[2]));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			absRot[i][j] = abs(rot[i][j]) + std::numeric_limits<float>::epsilon();
		}
	}

	//TODO: RETURN TO THIS, MIGHT BE GLOBAL
	for (int i = 0; i < 3; i++) {
		ra = myHalfW[i];
		rb = otherHalfW[0] * absRot[i][0] + otherHalfW[1] * absRot[i][1] + otherHalfW[2] * absRot[i][2];
		if (abs(translation[i]) > ra + rb) {
			return false;
		}
	}
	for (int i = 0; i < 3; i++) {
		ra = myHalfW[0] * absRot[0][i] + myHalfW[1] * absRot[1][i] + myHalfW[2] * absRot[2][i];
		rb = otherHalfW[i];
		if (abs(translation[0] * rot[0][i] + translation[1] * rot[1][i] + translation[2] * rot[2][i]) > ra + rb) {
			return false;
		}
	}

	//a0xb0
	ra = myHalfW[1] * absRot[2][0] + myHalfW[2] * absRot[1][0];
	rb = otherHalfW[1] * absRot[0][2] + otherHalfW[2] * absRot[0][1];
	if (abs(translation[2] * rot[1][0] - translation[1] * rot[2][0]) > ra + rb) {
		return false;
	}

	//a0xb1
	ra = myHalfW[1] * absRot[2][1] + myHalfW[2] * absRot[1][1];
	rb = otherHalfW[0] * absRot[0][2] + otherHalfW[2] * absRot[0][0];
	if (abs(translation[2] * rot[1][1] - translation[1] * rot[2][1]) > ra + rb) {
		return false;
	}

	//a0xb2
	ra = myHalfW[1] * absRot[2][2] + myHalfW[2] * absRot[1][2];
	rb = otherHalfW[0] * absRot[0][1] + otherHalfW[1] * absRot[0][0];
	if (abs(translation[2] * rot[1][2] - translation[1] * rot[2][2]) > ra + rb) {
		return false;
	}

	//a1xb0
	ra = myHalfW[0] * absRot[2][0] + myHalfW[2] * absRot[0][0];
	rb = otherHalfW[1] * absRot[1][2] + otherHalfW[2] * absRot[1][1];
	if (abs(translation[0] * rot[2][0] - translation[2] * rot[0][0]) > ra + rb) {
		return false;
	}

	//a1xb1
	ra = myHalfW[0] * absRot[2][1] + myHalfW[2] * absRot[0][1];
	rb = otherHalfW[0] * absRot[1][2] + otherHalfW[2] * absRot[1][0];
	if (abs(translation[0] * rot[2][1] - translation[2] * rot[0][1]) > ra + rb) {
		return false;
	}

	//a1xb2
	ra = myHalfW[0] * absRot[2][2] + myHalfW[2] * absRot[0][2];
	rb = otherHalfW[0] * absRot[1][1] + otherHalfW[1] * absRot[1][0];
	if (abs(translation[0] * rot[2][2] - translation[2] * rot[0][2]) > ra + rb) {
		return false;
	}

	//a2xb0
	ra = myHalfW[0] * absRot[1][0] + myHalfW[1] * absRot[0][0];
	rb = otherHalfW[1] * absRot[2][2] + otherHalfW[2] * absRot[2][1];
	if (abs(translation[1] * rot[0][0] - translation[0] * rot[1][0]) > ra + rb) {
		return false;
	}

	//a2xb1
	ra = myHalfW[0] * absRot[1][1] + myHalfW[1] * absRot[0][1];
	rb = otherHalfW[0] * absRot[2][2] + otherHalfW[2] * absRot[2][0];
	if (abs(translation[1] * rot[0][1] - translation[0] * rot[1][1]) > ra + rb) {
		return false;
	}

	//a2xb2
	ra = myHalfW[0] * absRot[1][2] + myHalfW[1] * absRot[0][2];
	rb = otherHalfW[0] * absRot[2][1] + otherHalfW[1] * absRot[2][0];
	if (abs(translation[1] * rot[0][2] - translation[0] * rot[1][2]) > ra + rb) {
		return false;
	}
	float c = abs(translation[1] * rot[0][2] - translation[0] * rot[1][2]);
	float d = ra + rb;

	return true;
}

float BoundingObject::dotProduct(vector3 a, vector3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

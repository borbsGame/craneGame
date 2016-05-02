#ifndef __BOUNDINGOBJECT_H_
#define __BOUNDINGOBJECT_H_

#include "RE\ReEng.h"


class BoundingObject
{
	float m_fRadius = 0.0f;
	vector3 m_v3Size = vector3(0.0f);
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_Color = REBLUE;
	bool m_isVisible = true;
	bool m_boxVisible = true;

	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Object Class

	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the Object Class

	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides


public:
	//Constructor
	BoundingObject(std::vector<vector3> a_lVectorList);

	//Copy Constructor
	BoundingObject(BoundingObject const& other);

	//Copy Assignment Operator
	BoundingObject& operator=(BoundingObject const& other);

	//Destructor
	~BoundingObject(void);

	//Changes object contents for other object's
	void Swap(BoundingObject& other);

	//Sets the Bounding Object into world coordinates
	void SetModelMatrix(matrix4 a_m4ToWorld);

	//Gets radius of Bounding object's collision sphere
	float GetRadius(void);

	//Checks if there is a collision with another Bounding sphere Object
	bool IsColliding(BoundingObject* const a_pOther);

	matrix4 GetModelMatrix(void);

	vector3 GetSize(void);

	//New Methods for Bounding Object
	void setVisibility(bool isVisible);
	bool getVisibility();

	void setBoxVisibility(bool isVisible);
	bool getBoxVisibility();

	void setColor(vector3 color);

	void drawBO(MeshManagerSingleton* meshMngr);

	float dotProduct(vector3 a, vector3 b);

	/*
	USAGE: Gets the Bounding Object's center in local coordinates
	ARGUMENTS: ---
	OUTPUT: Center's of the Object in local coordinates
	*/
	vector3 GetCenterLocal(void);
	/*
	USAGE: Gets the Bounding Object's center in global coordinates
	ARGUMENTS: ---
	OUTPUT: Center's of the Object in global coordinates
	*/
	vector3 GetCenterGlobal(void);
	/*
	USAGE: Gets the Bounding Object sizes for all sides (divided in half)
	ARGUMENTS: ---
	OUTPUT: HalfWidth Vector
	*/
	vector3 GetHalfWidth(void);
	/*
	USAGE: Gets the Bounding Object sizes for all sides (divided in half) reoriented
	ARGUMENTS: ---
	OUTPUT: HalfWidth Vector
	*/
	vector3 GetHalfWidthG(void);
	/*
	USAGE: Gets the min vector from the Oriented Bounding Box in local space
	ARGUMENTS: ---
	OUTPUT: Minimum in global space
	*/
	vector3 GetMin(void);
	/*
	USAGE: Gets the max vector from the Oriented Bounding Box in local space
	ARGUMENTS: ---
	OUTPUT: Maximum in global space
	*/
	vector3 GetMax(void);
	/*
	USAGE: Gets the min vector from the ReAlligned Bounding Box in global space
	ARGUMENTS: ---
	OUTPUT: Minimum in global space
	*/
	vector3 GetMinG(void);
	/*
	USAGE: Gets the max vector from the ReAlligned Bounding Box in global space
	ARGUMENTS: ---
	OUTPUT: Maximum in global space
	*/
	vector3 GetMaxG(void);
	/*
	USAGE: Displays the Bounding Sphere of the BO in the specified color
	ARGUMENTS:
	- vector3 a_v3Color = REDEFAULT -> Color of the Object to display if the value is REDEFAULT it
	-- will display Objects in white and colliding ones in red.
	OUTPUT: ---
	*/
	void DisplaySphere(MeshManagerSingleton* meshMngr);
	/*
	USAGE: Displays the Oriented Bounding Box of the BO in the specified color
	ARGUMENTS:
	- vector3 a_v3Color = REDEFAULT -> Color of the Object to display if the value is REDEFAULT it
	-- will display Objects in white and colliding ones in red.
	OUTPUT: ---
	*/
	void DisplayOriented(MeshManagerSingleton* meshMngr);
	/*
	USAGE: Displays the ReAlligned Bounding Box of the BO in the specified color
	ARGUMENTS:
	- vector3 a_v3Color = REDEFAULT -> Color of the Object to display if the value is REDEFAULT it
	-- will display Objects in white and colliding ones in red.
	OUTPUT: ---
	*/
	void DisplayReAlligned(MeshManagerSingleton* meshMngr);

	bool RunSAT(BoundingObject* const a_pOther);

private:

	void Release(void);

	void Init(void);
};

#endif //__BOUNDINGOBJECT_H_

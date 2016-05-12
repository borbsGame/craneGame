#include "MyOctant.h"
using namespace ReEng;
//  MyOctant
bool MyOctant::m_bHead = true;
void MyOctant::Init(void)
{
	m_v3Position = vector3(0.0f);
	m_fSize = 0.0f;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_nChildCount = 0;
	m_pEMngr = EntityManager::GetInstance();


	if (m_bHead) {
		//code for checking the size of the octree
		uint nObjectCount = m_pEMngr->GetEntityCount();

		BoundingObject* pBO = m_pEMngr->getEntity(0)->getBO();
		vector3 vMaxG = pBO->GetMaxG();
		vector3 vMinG = pBO->GetMinG();

		for (int i = 0; i < nObjectCount; i++)
		{
			BoundingObject* pBO = m_pEMngr->getEntity(i)->getBO();
			vector3 vMax = pBO->GetMaxG();
			vector3 vMin = pBO->GetMinG();
			//checking the X
			if (vMax.x > vMaxG.x) { vMaxG.x = vMax.x; }
			else if (vMin.x < vMinG.x) { vMinG.x = vMin.x; }
			//checking the Y
			if (vMax.y > vMaxG.y) { vMaxG.y = vMax.y; }
			else if (vMin.y < vMinG.y) { vMinG.y = vMin.y; }
			//checking the Z
			if (vMax.z > vMaxG.z) { vMaxG.z = vMax.z; }
			else if (vMin.z < vMinG.z) { vMinG.z = vMin.z; }

			if (m_pEMngr->getEntity(i)->getType() == "Player") {
				std::cout << "test";
			}
		}
		m_v3Position = (vMinG + vMaxG) / 2.0f;
		float sizeX = glm::distance(vector3(vMinG.x, 0, 0), vector3(vMaxG.x, 0, 0));
		float sizeY = glm::distance(vector3(0, vMinG.y, 0), vector3(0, vMaxG.y, 0));
		float sizeZ = glm::distance(vector3(0, 0, vMinG.z), vector3(0, 0, vMaxG.z));
		m_fSize = sizeX;
		if (m_fSize < sizeY) m_fSize = sizeY;
		if (m_fSize < sizeZ) m_fSize = sizeZ;
	}
}
void MyOctant::Swap(MyOctant& other)
{

}
void MyOctant::Release(void)
{

}
//The big 3
MyOctant::MyOctant(float a_fSize)
{
	Init();
	m_fSize = a_fSize;
}
MyOctant::MyOctant() { Init(); }
MyOctant::MyOctant(MyOctant const& other)
{

}
MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant() { Release(); };
//Accessors

//--- Non Standard Singleton Methods

void MyOctant::Display(void)
{
	for (uint n = 0; n < m_nChildCount; n++)
	{
		m_pChildren[n].Display();
	}
	m_pMeshMngr->AddCubeToQueue(glm::translate(m_v3Position) * glm::scale(vector3(m_fSize)), REWHITE, WIRE);
}

void MyOctant::Subdivide(void)
{

	uint nObjectCount = m_pEMngr->GetEntityCount();
	/*m_uChildren = 8;
	m_pChildren = new MyOctant[m_uChildren];
	for (uint index = 0; index < 8; index++)
	{
	m_pChildren[index].m_fSize = this->m_fSize / 2.0f;
	m_pChildren[index].m_v3Center = this->m_v3Center;
	m_pChildren[index].m_v3Center.x += m_pChildren[index].m_fSize / 2.0f;
	m_pChildren[index].m_v3Center.y += m_pChildren[index].m_fSize / 2.0f;
	m_pChildren[index].m_v3Center.z += m_pChildren[index].m_fSize / 2.0f;
	}*/

	m_bHead = false;

	m_pChildren = new MyOctant[8];
	m_nChildCount = 8;
	float fNewSize = this->m_fSize / 2;
	for (uint index = 0; index < 8; index++)
	{
		m_pChildren[index].m_fSize = fNewSize;
		m_pChildren[index].m_v3Position = m_v3Position;
	}
	fNewSize /= 2.0f;

	//for the index 0
	m_pChildren[0].m_v3Position.x += fNewSize;
	m_pChildren[0].m_v3Position.y += fNewSize;
	m_pChildren[0].m_v3Position.z += fNewSize;

	//for the index 1
	m_pChildren[1].m_v3Position.x -= fNewSize;
	m_pChildren[1].m_v3Position.y += fNewSize;
	m_pChildren[1].m_v3Position.z += fNewSize;

	//for the index 2
	m_pChildren[2].m_v3Position.x -= fNewSize;
	m_pChildren[2].m_v3Position.y -= fNewSize;
	m_pChildren[2].m_v3Position.z += fNewSize;

	//for the index 3
	m_pChildren[3].m_v3Position.x += fNewSize;
	m_pChildren[3].m_v3Position.y -= fNewSize;
	m_pChildren[3].m_v3Position.z += fNewSize;

	//for the index 4
	m_pChildren[4].m_v3Position.x += fNewSize;
	m_pChildren[4].m_v3Position.y += fNewSize;
	m_pChildren[4].m_v3Position.z -= fNewSize;

	//for the index 5
	m_pChildren[5].m_v3Position.x -= fNewSize;
	m_pChildren[5].m_v3Position.y += fNewSize;
	m_pChildren[5].m_v3Position.z -= fNewSize;

	//for the index 6
	m_pChildren[6].m_v3Position.x -= fNewSize;
	m_pChildren[6].m_v3Position.y -= fNewSize;
	m_pChildren[6].m_v3Position.z -= fNewSize;

	//for the index 7
	m_pChildren[7].m_v3Position.x += fNewSize;
	m_pChildren[7].m_v3Position.y -= fNewSize;
	m_pChildren[7].m_v3Position.z -= fNewSize;

	for (int i = 0; i < 8; i++)
	{
		vector3 vMaxG = m_pChildren[i].m_v3Position + vector3(m_pChildren[i].m_fSize);
		vector3 vMinG = m_pChildren[i].m_v3Position - vector3(m_pChildren[i].m_fSize);
		for (int j = 0; j < nObjectCount; j++)
		{
			BoundingObject* pBO = m_pEMngr->GetBoundingObject(j);
			vector3 vMax = pBO->GetMaxG();
			vector3 vMin = pBO->GetMinG();

			if (vMax.x < vMaxG.x)
				if (vMin.x > vMinG.x)
					if (vMax.y < vMaxG.y)
						if (vMin.y > vMinG.y)
							if (vMax.z < vMaxG.z)
								if (vMin.z > vMinG.z)
								{
									m_pChildren[i].objInside.push_back(pBO);
								}

		}

		if (m_pChildren[i].objInside.size() > 4)
		{
			m_pChildren[i].Subdivide();
		}
	}
}
void MyOctant::ReleaseChildren(void)
{
	if (m_pChildren != nullptr)
	{
		delete[] m_pChildren;
		m_pChildren = nullptr;
	}
}
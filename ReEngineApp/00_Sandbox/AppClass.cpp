#include "AppClass.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up

	m_m4Falcon = matrix4();
	m_m4FalconLeg = matrix4();

<<<<<<< HEAD
	falconMove = vector3(0.0f, 85.0f, 0.0f);

	//Load a model onto the Mesh manager
=======
	//Load models onto the Mesh manager
>>>>>>> f11d19b3243c61da648bf0669ffeb917e6fe5b55
	m_pMeshMngr->LoadModel("Birbs\\birb1.fbx", "Falcon");
	m_pMeshMngr->LoadModel("Birbs\\falconLeg.fbx", "FalconLeg");
	m_pMeshMngr->LoadModel("Birbs\\nest.fbx", "Nest");

	srand(time(NULL));
	//Iterate through prey list, load models and create positions
	for (int i = 0; i < numPrey; i++) {
		String sInstance = "Birb_" + std::to_string(i);
		m_pMeshMngr->LoadModel("Birbs\\birb1.fbx", sInstance);

		if(rand() % 2 == 0) preyList.push_back(vector3(rand() % 80, 0.0f, 0.0f));
		else preyList.push_back(vector3(rand() % 100 * -1, 0.0f, 0.0f));
		
	}
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matricies for models
	//Falcon Models
	m_pMeshMngr->SetModelMatrix(glm::scale(vector3(.1, .1, .1)) * glm::translate(falconMove) * ToMatrix4(m_qArcBall), "Falcon");
<<<<<<< HEAD

	m_m4FalconLeg = glm::scale(vector3(.1, 50, .1));
	//m_m4FalconLeg *= glm::translate(falconMove);

	//m_pMeshMngr->
	m_pMeshMngr->SetModelMatrix(glm::scale(vector3(.1, 15, .1)) * glm::translate(vector3(falconMove.x, 3 -legMove, .1)) * ToMatrix4(m_qArcBall), "FalconLeg");
=======
	m_pMeshMngr->SetModelMatrix(glm::scale(vector3(.1, .3, .1)) * glm::translate(falconMove) * glm::translate(0.0f,-.1f,0.0f)  * ToMatrix4(m_qArcBall), "FalconLeg");

	//Nest Model
	m_pMeshMngr->SetModelMatrix(glm::scale(vector3(.3, .3, .3)) * glm::translate(25.0f, 0.0f, 0.0f), "Nest");

	//Set Model Matrices for all birbs in preylist
	for (int i = 0; i < numPrey; i++) {
		 m_pMeshMngr->SetModelMatrix(glm::scale(vector3(.07, .07, .07)) * glm::translate(preyList[i]), "Birb_" + std::to_string(i));
	}
>>>>>>> f11d19b3243c61da648bf0669ffeb917e6fe5b55
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}
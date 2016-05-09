#include "AppClass.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Birb Craner"); // Window Name

	//Here for changing the screen resolution
	m_pSystem->SetWindowHeight(1000);
	m_pSystem->SetWindowWidth(800);

	//Color is set to CREAM 
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(1.0f, 0.92f, 0.81f, 0.0f);
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

	//Debug mode is off
	debugMode = false;

	//Updates the Physics for each Entity or object that needs it in the window
	entityManager = EntityManager::GetInstance();
	entityManager->setMeshManager(m_pMeshMngr);

	//Initialize Player and the falcon claw
	m_pMeshMngr->LoadModel("Birbs\\falconBody.fbx", "Falcon");
	player = new Player("Falcon", m_pMeshMngr);
	player->setPosition(vector3(0.0f, 8.0f, 0.0f));
	entityManager->addEntity(player);

	m_pMeshMngr->LoadModel("Birbs\\falconClaw.fbx", "FalconClaw");
	claw = new Claw("FalconClaw", m_pMeshMngr);
	claw->setPosition(vector3(0.0f, 8.0f, 0.0f));
	entityManager->addEntity(claw);

	//Load models onto the Mesh manager
	m_pMeshMngr->LoadModel("Birbs\\falconLeg.fbx", "FalconLeg");
	
	//Initialize Hawks
	for (int i = 0; i <= hawkNum; i++) {
		String sInstance = "Hawk_" + std::to_string(i);
		m_pMeshMngr->LoadModel("Birbs\\hawkBody.fbx", sInstance);
		hawks.push_back(new Hawk(sInstance, m_pMeshMngr));
		//for hawk positions
		if (rand() % 2 == 0) hawks.at(i)->setPosition(vector3(rand() % 5, 5.0 - i, 0.0f));
		else hawks.at(i)->setPosition(vector3(rand() % 5 * -1, 5.0 + i, 0.0f));

		entityManager->addEntity(hawks.at(i));
	}
	//Iterate through prey list, load models and create positions
	for (int i = 0; i < 8; i++) {
		String sInstance = "Birb_" + std::to_string(i);
		m_pMeshMngr->LoadModel("Birbs\\birbBody.fbx", sInstance);
		Birb* birb = new Birb(sInstance, m_pMeshMngr);
		//for birb positions
		if(rand() % 2 == 0) birb->setPosition(vector3(rand() % 5, 0.0f, 0.0f));
		else birb->setPosition(vector3(rand() % 5 * -1, 0.0f, 0.0f));
		
		entityManager->addEntity(birb);
	}

	//Add in the background
	m_pMeshMngr->LoadModel("Birbs\\backG.fbx", "Background");

	srand(time(NULL));
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
	
	//Update each Hawk and set their model matrix to draw it
	for (int i = 0; i <= hawkNum; i++) {
		String hawkModel = "Hawk_" + std::to_string(i);
		hawks.at(i)->getBO()->SetModelMatrix(m_pMeshMngr->GetModelMatrix(hawkModel));
		hawks.at(i)->getBO()->drawBO(m_pMeshMngr);
	}

	//to set the leg at the position of the player
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(player->getPosition().x, 
														player->getPosition().y, 
														player->getPosition().z))* glm::translate(vector3(0.0f, -legMove * 0.1, 0.0f)) * glm::scale(vector3(1.0f, legMove, 1.0f)),
														"FalconLeg");
	
	//to set the position of the claw in relation to the player's leg (see above)
	vector3 temp;
	temp = vector3(player->getPosition().x, 
						player->getPosition().y, 
						player->getPosition().z);
	temp += vector3(0.0f, -legMove *.2, 0.0f);
	claw->setPosition(temp);

	//update every thing on screen that is moveable 
	entityManager->setModelMatricies();
	entityManager->updateEntities();
	entityManager->checkCollisions();

	//set the player matrix and draw it
	player->getBO()->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Falcon"));
	player->getBO()->drawBO(m_pMeshMngr);
	
	//set the player's claw matrix and draw it
	claw->getBO()->SetModelMatrix(m_pMeshMngr->GetModelMatrix("FalconClaw"));
	claw->getBO()->drawBO(m_pMeshMngr);

	//Render and draw all the objects on to the screen
	entityManager->renderAllBO();

	//to get the time for the equation 
	//get time between calls
	double fCallTime = m_pSystem->LapClock();
	//counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;
	static double bounce = fRunTime;


	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//if Debug mode is on, show FPS and Name
	 if (debugMode){
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), RERED);
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	 }
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode (if debugMode is on):
	if (debugMode){
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
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}
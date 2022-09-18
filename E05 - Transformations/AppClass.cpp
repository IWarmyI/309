#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Darvin Muralitharan - dm1250@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Allocate the memory for the Meshes
	m_uMeshCount = 46;

	for (int i = 0; i < m_uMeshCount; i++)
	{
		MyMesh* mesh = new MyMesh();
		meshes.push_back(mesh);
		meshes[i]->GenerateCube(1.0f, C_BLACK);
	}
		
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//starting pos
	static float xMove = -10.0f;
	vector3 position(xMove, 0.0f, 0.0f);

	//move left to right
	static float translate = 0.01f;
	position.x = xMove + translate;
	translate += 0.01f;
	matrix4 m4Position = glm::translate(position);

	//set block positions
	int i = 0;

	//first row
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, 0.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, 0.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, 0.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7.0f, 0.0f, 0.0f))); i++;

	//second row
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, 1.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, 1.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f, 1.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(10.0f, 1.0f, 0.0f))); i++;

	//third row
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, 2.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, 2.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, 2.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, 2.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, 2.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, 2.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7.0f, 2.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f, 2.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(10.0f, 2.0f, 0.0f))); i++;

	//fourth row
	for (int block = 0; block < 11; block++)
	{
		meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(block, 3.0f, 0.0f))); i++;
	}

	//fifth row
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, 4.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, 4.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, 4.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, 4.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, 4.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f, 4.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(9.0f, 4.0f, 0.0f))); i++;

	//sixth row
	for (int block = 2; block < 9; block++)
	{
		meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(block, 5.0f, 0.0f))); i++;
	}

	//seventh row
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3, 6.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7, 6.0f, 0.0f))); i++;

	//eight row
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2, 7.0f, 0.0f))); i++;
	meshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8, 7.0f, 0.0f))); i++;

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release meshes
	for (int i = 0; i < m_uMeshCount; i++)
	{
		SafeDelete(meshes[i]);
	}

	//release GUI
	ShutdownGUI();
}
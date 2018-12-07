////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Model2 = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_SkyDome = 0;
	m_Tree = 0;
	m_Trees = {};
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.5f, -10.0f);
	
	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/floor.txt", L"../Engine/data/forestfloor.jpg");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_Model->SetPosition(0.0f, 0.0f, 2.0f);

	// Create the model object.
	m_Model2 = new ModelClass;
	if (!m_Model2)
	{
		return false;
	}
	
	// Initialize the model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/wall.txt", L"../Engine/data/wall.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_Model2->SetPosition(0.0f, -1.0f, 20.0f);

	// Create the tree object.
	m_Tree = new TreeClass;
	if (!m_Tree)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Tree->Initialize(m_D3D->GetDevice(), hwnd, 2.0f, -1.0f, 2.0f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the tree object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 5.0f);
	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);

	// Create the sky dome object.
	m_SkyDome = new ModelClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_D3D->GetDevice(), "../Engine/data/skydome.txt", L"../Engine/data/SunSet/SunSetFront2048.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}
	
	// Initialize the tree list.
	for (int i = 0; i < 20; i++)
	{
		TreeClass* tree = new TreeClass;
		m_Trees.push_back(tree);
		result = tree->Initialize(m_D3D->GetDevice(), hwnd, i, 0.0f, i % 5);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the tree object.", L"Error", MB_OK);
			return false;
		}
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the model object.
	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	// Release the tree object.
	if (m_Tree)
	{
		m_Tree->Shutdown();
		delete m_Tree;
		m_Tree = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Releases the tree list.
	m_Trees.clear();
	m_Trees = {};
	
	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;
	static float delta =0.0f;


	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.01f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Update the delta variable each frame. (keep this between 0 and 1)
	delta += 0.001;
	if(delta >1.0f)
	{
		delta -=1.0f;
	}
	
	// Render the graphics scene.
	result = Render(rotation, delta);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation, float deltavalue)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	D3DXVECTOR3 cameraPosition;
	bool result;
	float xPos, yPos, zPos;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	// Turn off back face culling.
	m_D3D->TurnOffCulling();

	// Turn off the Z buffer.
	m_D3D->TurnZBufferOff();

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_D3D->GetDeviceContext());

	m_LightShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue,
		m_SkyDome->GetTexture(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	// Turn back face culling back on.
	m_D3D->TurnOnCulling();

	// Turn the Z buffer back on.
	m_D3D->TurnZBufferOn();

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	// D3DXMatrixRotationYawPitchRoll(&worldMatrix, rotation, rotation, rotation);

	D3DXVECTOR3 tempvec = m_Model->GetPosition();
	xPos = tempvec.x;
	yPos = tempvec.y;
	zPos = tempvec.z;
	D3DXMatrixTranslation(&worldMatrix, xPos, yPos, zPos);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
								    m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue,
								m_Model->GetTexture(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	D3DXVECTOR3 tempvec2 = m_Model2->GetPosition();
	xPos = tempvec2.x;
	yPos = tempvec2.y;
	zPos = tempvec2.z;
	D3DXMatrixTranslation(&worldMatrix, xPos, yPos, zPos);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model2->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue,
		m_Model2->GetTexture(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	//ModelClass* trunk = m_Tree->GetTrunk();
	//D3DXVECTOR3 tempvec3 = trunk->GetPosition();
	//xPos = tempvec3.x;
	//yPos = tempvec3.y;
	//zPos = tempvec3.z;
	//D3DXMatrixTranslation(&worldMatrix, xPos, yPos, zPos);
	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//trunk->Render(m_D3D->GetDeviceContext());

	//// Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), trunk->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue,
	//	trunk->GetTexture(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//if (!result)
	//{
	//	return false;
	//}

	//ModelClass* leaves = m_Tree->GetLeaves();
	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//leaves->Render(m_D3D->GetDeviceContext());

	//// Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), leaves->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue,
	//	leaves->GetTexture(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	/*if (!result)
	{
		return false;
	}*/

	for (std::list<TreeClass*>::iterator it=m_Trees.begin(); it != m_Trees.end(); ++it)
	{
		TreeClass* tree = *it;
		ModelClass* trunk = tree->GetTrunk();
		D3DXVECTOR3 tempvec3 = trunk->GetPosition();
		xPos = tempvec3.x;
		yPos = tempvec3.y;
		zPos = tempvec3.z;
		D3DXMatrixTranslation(&worldMatrix, xPos, yPos, zPos);
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		trunk->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), trunk->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue,
			trunk->GetTexture(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		ModelClass* leaves = tree->GetLeaves();
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		leaves->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), leaves->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->GetAmbientColor(), deltavalue,
			leaves->GetTexture(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::ChangeCamera(float changeX, float changeZ, float rotatorY)
{
	D3DXVECTOR3 newRot = m_Camera->GetRotation();
	newRot.y += rotatorY;
	m_Camera->SetRotation(newRot.x, newRot.y, newRot.z);
	float radians;
	D3DXVECTOR3 newPos = m_Camera->GetPosition();
	radians = m_Camera->GetRotation().y * 0.0174532925f;
	newPos.x += cosf(radians) * changeX;
	newPos.z += -sinf(radians) * changeX;
	newPos.x += sinf(radians) * changeZ;
	newPos.z += cosf(radians) * changeZ;
	m_Camera->SetPosition(newPos.x, newPos.y, newPos.z);
	
}
////////////////////////////////////////////////////////////////////////////////
// Filename: treeclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "treeclass.h"

TreeClass::TreeClass()
{
	m_Trunk = 0;
	m_Leaves = 0;

}


TreeClass::TreeClass(const TreeClass& other)
{
}


TreeClass::~TreeClass()
{
}

bool TreeClass::Initialize(ID3D11Device* device, HWND hwnd, float x, float y, float z)
{
	bool result;

	// Create the model object.
	m_Trunk = new ModelClass;
	if (!m_Trunk)
	{
		return false;
	}

	// Initialize the trunk object.
	result = m_Trunk->Initialize(device, "../Engine/data/Tree_Trunk.txt", L"../Engine/data/bark_0021.jpg", L"../Engine/data/barkN.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_Trunk->SetPosition(x, y, z);

	// Create the model object.
	m_Leaves = new ModelClass;
	if (!m_Leaves)
	{
		return false;
	}

	// Initialize the leaves object.
	result = m_Leaves->Initialize(device, "../Engine/data/Tree_Leaves.txt", L"../Engine/data/Leaf_UV.jpg", L"../Engine/data/leavesN.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_Leaves->SetPosition(x, y, z);

	return true;
}

void TreeClass::Shutdown()
{
	if (m_Trunk)
	{
		m_Trunk->Shutdown();
		delete m_Trunk;
		m_Trunk = 0;
	}

	if (m_Leaves)
	{
		m_Leaves->Shutdown();
		delete m_Leaves;
		m_Trunk = 0;
	}
}

void TreeClass::Render(ID3D11DeviceContext* deviceContext)
{
	m_Trunk->Render(deviceContext);
	m_Leaves->Render(deviceContext);
}


ModelClass* TreeClass::GetTrunk()
{
	return m_Trunk;
}

ModelClass* TreeClass::GetLeaves()
{
	return m_Leaves;
}
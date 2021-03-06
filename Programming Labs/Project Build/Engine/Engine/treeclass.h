////////////////////////////////////////////////////////////////////////////////
// Filename: treeclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TREECLASS_H_
#define _TREECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "modelclass.h"
#include "d3dclass.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: TreeClass
////////////////////////////////////////////////////////////////////////////////
class TreeClass
{
public:
	TreeClass();
	TreeClass(const TreeClass&);
	~TreeClass();

	bool Initialize(ID3D11Device*, HWND hwnd, float x, float y, float z);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	ModelClass* GetTrunk();
	ModelClass* GetLeaves();

private:
	ModelClass *m_Trunk;
	ModelClass *m_Leaves;

};
#endif
////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "treeclass.h"
#include "rendertextureclass.h"
#include "shadowshaderclass.h"
#include "depthshaderclass.h"
#include <math.h>
#include <list>


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	void ChangeCamera(float, float, float);

private:
	bool RenderSceneToTexture();
	bool Render(float, float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass *m_Model, *m_Model2;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	ModelClass* m_SkyDome;
	TreeClass* m_Tree;
	list<TreeClass*> m_Trees;
	RenderTextureClass* m_RenderTexture;
	ShadowShaderClass* m_ShadowShader;
	DepthShaderClass* m_DepthShader;
};
#endif
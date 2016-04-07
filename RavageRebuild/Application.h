#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include "RavRenderCore.h"
#include "RavFileSystem.h"
#include "RavConfigFile.h"
#include "RavTransform.h"
#include "RavTimer.h"

#include "MeshLoaderObj.h"
#include "Camera.h"
#include "Light.h"

using Ravage::Shader;
using Ravage::Transform;
using Ravage::Matrix4;
using Ravage::Vector2;

class Application
{
public:
	Application();
	~Application();

	bool run();
	void update();
	void render();
	void renderScene();

private:
	bool initialize();
	bool loadScene();

	bool setShader(Shader& shader);
	bool setLight(Light& l);
	bool setTransform(Transform& t);
	bool drawMesh(MeshLoaderObj& obj);
	bool drawQuad(Ravage::Texture* src, Ravage::Texture* dest, int pass);
	Ravage::Texture2D* loadImage(const Ravage::String& filename);

	void attachLight(const Light& light);

	Ravage::RenderCore* mRenderCore;
	Ravage::Renderer* mRenderer;
	Ravage::FileSystem* mFileSystem;
	Ravage::Timer mTimer;

	Ravage::RenderTexture* mShadowMap;
	Ravage::RenderTexture* mShadowMapBlur;

	Ravage::RenderTexture* mDepthMap;
	Ravage::RenderTexture* mRenderTarget1;
	Ravage::RenderTexture* mRenderTarget2;

	Ravage::VertexBuffer* mQuadBuffer;
	Ravage::VertexData* mQuadData;
	Ravage::VertexDeclaration mQuadDeclaration;
	
	Ravage::Texture2D* mNormalTexture;
	Ravage::Texture2D* mHeightTexture;

	unsigned long mDelta;
	
	int mPosX;
	int mPosY;
	POINT mLastPoint;

	bool mShadowScene;
	Shader* mCurShader;
	Transform* mCurTransform;
	Light* mCurLight;

	Camera mLight1Camera;
	Ravage::Vector2 mLight1Angles;

	Camera mMainCamera;
	Ravage::Vector2 mMainAngles;
	
	Ravage::Vector2* mCurrentAngles;
	Camera* mCurrentCamera;

	bool mUsePosteffects;

	Transform mTeapotTransform;
	Transform mTeapotTransform2;
	Transform mPlaneTransform;

	MeshLoaderObj mTeapot;
	MeshLoaderObj mPlane;

	Light mLight1;

	Shader mDiffuseShader;
	Shader mCookTorranceShader;
	Shader mShadowShader;
	Shader mQuadShader;
	Shader mBlurShader;
	Shader mBlackWhiteShader;
	Shader mDofShader;
	Shader mParallaxShader;
};


#endif /* APPLICATION_H_INCLUDED */
#include "Application.h"
#include "OpenGL\RavUtilitiesOpenGL.h"
#include "png.h"

#pragma comment(lib, "libpng.lib")

Application::Application() :
	mRenderCore(Ravage::RenderCore::instance()),
	mRenderer(0),
	mFileSystem(Ravage::FileSystem::instance()),
	mShadowMap(0),
	mShadowMapBlur(0),
	mDepthMap(0),
	mRenderTarget1(0),
	mRenderTarget2(0),
	mQuadBuffer(0),
	mQuadData(0),
	mNormalTexture(0),
	mDelta(0),
	mShadowScene(false),
	mCurShader(0),
	mCurTransform(0),
	mCurLight(0),
	mLight1Angles(Ravage::Vector2::ZERO),
	mMainAngles(Ravage::Vector2::ZERO),
	mCurrentAngles(&mMainAngles),
	mCurrentCamera(&mMainCamera),
	mUsePosteffects(false)
{}

Application::~Application()
{
	if (mShadowMap)
		mRenderer->release(mShadowMap);

	if (mShadowMapBlur)
		mRenderer->release(mShadowMapBlur);

	if (mDepthMap)
		mRenderer->release(mDepthMap);

	if (mNormalTexture)
		mRenderer->release(mNormalTexture);

	if (mHeightTexture)
		mRenderer->release(mHeightTexture);

	if (mRenderTarget1)
		mRenderer->release(mRenderTarget1);

	if (mRenderTarget2)
		mRenderer->release(mRenderTarget2);

	if (mQuadData)
		mRenderer->release(mQuadData);

	if (mQuadBuffer)
		mRenderer->release(mQuadBuffer);

	mRenderCore->freeInst();
	mFileSystem->freeInst();
}

bool Application::initialize()
{
	if (!mFileSystem->initialize())
		return false;

	Ravage::ConfigFile file;
	file.load(RAV_TXT("config.txt"));

	Ravage::Settings* settings = Ravage::Settings::instance();
	Ravage::Vector2 size = settings->getDisplaySettings()->getWindowResolution();
	mMainCamera.setAspect(size.x / size.y);

	settings->freeInst();

	Ravage::UtilitiesOpenGL::registerLibrary();
	
	if (!mRenderCore->initialize())
		return false;

	mRenderer = mRenderCore->getRenderer();

	mRenderer->setRenderState(Ravage::RS_ZENABLE, true);
	//mRenderer->setRenderState(Ravage::RS_ZVALUE, 1.0f);
	//mRenderer->setRenderState(Ravage::RS_ZFUNC, Ravage::CMP_GREATER);

	Real quadData[] = {-1.0f, 1.0f, -1.0f, -1.0f, 1.0f,  1.0f,
						1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f};

	mQuadBuffer = mRenderer->createVertexBuffer(sizeof(Real) * 12, Ravage::GR_TYPE_STATIC);
	mQuadBuffer->setBuffer((Ravage::Byte*)quadData, sizeof(Real) * 12);

	mQuadDeclaration.addElement(0, Ravage::VertexDeclaration::TYPE_REAL2, Ravage::VertexDeclaration::USAGE_POSITION);

	mQuadData = mRenderer->createVertexData(&mQuadDeclaration);
	mQuadData->addStream(mQuadBuffer);
	mQuadData->generateStreamInfo();

	mShadowMap = mRenderer->createRenderTexture(Vector2(512, 512), Ravage::RTF_RG32F, 32);
	mShadowMap->setFilterMode(Ravage::FM_POINT);

	mShadowMapBlur = mRenderer->createRenderTexture(Vector2(512, 512), Ravage::RTF_RG32F, 32);
	mShadowMapBlur->setFilterMode(Ravage::FM_POINT);

	mDepthMap = mRenderer->createRenderTexture(size, Ravage::RTF_RG32F, 32);
	mDepthMap->setFilterMode(Ravage::FM_POINT);

	mRenderTarget1 = mRenderer->createRenderTexture(size, Ravage::RTF_RGBA8, 24);
	mRenderTarget1->setFilterMode(Ravage::FM_POINT);

	mRenderTarget2 = mRenderer->createRenderTexture(size, Ravage::RTF_RGBA8, 0);
	mRenderTarget2->setFilterMode(Ravage::FM_POINT);

	return true;
}

bool Application::loadScene()
{
	mQuadShader.load(RAV_TXT("quad.shader"));
	mQuadShader.compile();

	mShadowShader.load(RAV_TXT("shadow.shader"));
	mShadowShader.compile();

	mDiffuseShader.load(RAV_TXT("diffuse.shader"));
	mDiffuseShader.compile();

	mCookTorranceShader.load(RAV_TXT("cook.shader"));
	mCookTorranceShader.compile();

	mBlurShader.load(RAV_TXT("blur.shader"));
	mBlurShader.compile();

	mBlackWhiteShader.load(RAV_TXT("blackwhite.shader"));
	mBlackWhiteShader.compile();

	mDofShader.load(RAV_TXT("dof.shader"));
	mDofShader.compile();

	mParallaxShader.load(RAV_TXT("parallax.shader"));
	mParallaxShader.compile();
	
	mNormalTexture = loadImage(RAV_TXT("rocks.png"));
	mNormalTexture->setWrapMode(Ravage::TWM_REPEAT);

	mHeightTexture = loadImage(RAV_TXT("rocks_height.png"));
	mHeightTexture->setWrapMode(Ravage::TWM_REPEAT);

	mTeapotTransform.setLocalPosition(Vector3(0, 0, 10));
	mTeapotTransform.setLocalRotation(Vector3(-Ravage::Math::PI_2 / 2, 0, 0));
	mTeapotTransform.setLocalScale(Vector3(1, 1, 1));

	mTeapotTransform2.setLocalPosition(Vector3(4, -2, 8));
	mTeapotTransform2.setLocalRotation(Vector3(-Ravage::Math::PI_2 / 2, 0, 0));
	mTeapotTransform2.setLocalScale(Vector3(1, 1, 1));

	mPlaneTransform.setLocalPosition(Vector3(0, -5, 10));
	mPlaneTransform.setLocalRotation(Vector3(0, 0, 0));
	mPlaneTransform.setLocalScale(Vector3(1, 1, 1));

	mLight1Camera = Camera(mLight1.getAngle(), 1.0f, 0.03f, mLight1.getRange());

	mLight1Camera.getTransform().setLocalPosition(Vector3(0, 10, 10));
	mLight1Camera.getTransform().setLocalRotation(Vector3(Ravage::Math::PI_2, 0, 0));
	mLight1Camera.getTransform().setLocalScale(Vector3(1, 1, 1));

	mTeapot.load(RAV_TXT("teapot.obj"));
	mPlane.load(RAV_TXT("plane.obj"));

	return true;
}

void Application::render()
{	
	Ravage::RenderTexture* src = mRenderTarget1;
	Ravage::RenderTexture* dest = mRenderTarget2;

	setLight(mLight1);

	//SHADOW MAP
	mShadowScene = true;
	mRenderer->beginScene(mShadowMap);
	attachLight(mLight1);
	mRenderer->clear(Ravage::CM_DEPTH | Ravage::CM_TARGET);
	renderScene();
	mRenderer->endScene();

	//SHADOW MAP BLUR
	mShadowScene = false;
	mRenderer->setRenderState(Ravage::RS_ZENABLE, false);
	setShader(mBlurShader);
	drawQuad(mShadowMap, mShadowMapBlur, 0);
	drawQuad(mShadowMapBlur, mShadowMap, 1);
	mRenderer->setRenderState(Ravage::RS_ZENABLE, true);

	//SCENE RENDER
	mShadowScene = false;
	mRenderCore->setProjectionMatrix(mCurrentCamera->getProjectionMatrix());
	mRenderCore->setViewMatrix(mCurrentCamera->getViewMatrix());
	mRenderer->beginScene(src);
	mRenderer->clear(Ravage::CM_DEPTH | Ravage::CM_TARGET);
	renderScene();
	mRenderer->endScene();

	//DEPTH MAP (Best way is to use FBO with depth texture)
	mShadowScene = true;
	mRenderer->beginScene(mDepthMap);
	mRenderer->clear(Ravage::CM_DEPTH | Ravage::CM_TARGET);
	renderScene();
	mRenderer->endScene();

	//DEPTH OF FIELD
	mShadowScene = false;
	mRenderer->setRenderState(Ravage::RS_ZENABLE, false);
	setShader(mDofShader);
	drawQuad(src, dest, 0);
	std::swap(src, dest);

	//POST-EFFECTS
	mShadowScene = false;
	if (mUsePosteffects)
	{
		setShader(mBlurShader);
		drawQuad(src, dest, 0);
		drawQuad(dest, src, 1);
		setShader(mBlackWhiteShader);
		drawQuad(src, dest, 0);
		std::swap(dest, src);
	}

	//SHOW RESULT
	mShadowScene = false;
	setShader(mQuadShader);
	drawQuad(src, 0, 0);
	mRenderer->setRenderState(Ravage::RS_ZENABLE, true);
}

void Application::attachLight(const Light& light)
{
	Real nearClip = 0.03f;
	Real farClip = light.getRange();

	mLight1.getTransform().setLocalPosition(mLight1Camera.getTransform().getLocalPosition());
	mLight1.getTransform().setLocalRotation(mLight1Camera.getTransform().getLocalRotation());

	mRenderCore->setProjectionMatrix(mLight1Camera.getProjectionMatrix());
	mRenderCore->setViewMatrix(mLight1Camera.getViewMatrix());
}

bool Application::drawMesh(MeshLoaderObj& obj)
{
	RavAssert(mCurShader);
	RavAssert(mCurTransform);
	RavAssert(mCurLight);

	Real nearClip = 0.03f;
	Real farClip = mCurLight->getRange();

	Matrix4 lightViewProj = Matrix4::concatenate(mLight1Camera.getViewMatrix(), mLight1Camera.getProjectionMatrix());

	Matrix4 view  = mRenderCore->getViewMatrix();
	Matrix4 proj  = mRenderCore->getProjectionMatrix();
	Matrix4 world = mCurTransform->getWorldMatrix();

	Matrix4 worldView = Matrix4::concatenate(world, view);
	Matrix4 worldViewProj = Matrix4::concatenate(worldView, proj);

	Matrix4 worldInv = world.inverseAffine();
	Matrix4 normalMatrix = worldInv.transpose();
	                                                                                                                                                                                                                                                                                                                               
	mRenderer->loadVertexData(obj.getVertexData());

	int count = mCurShader->getPassCount();
	for (int i = 0; i < count; i++)
	{
		mCurShader->beginPass(i);

		Ravage::ShaderPass* pass = mCurShader->getPass(i);
		unsigned id = pass->getUniformId(RAV_TXT("light.position"));
		pass->setUniform(id, mCurLight->getTransform().getLocalPosition());

		id = pass->getUniformId(RAV_TXT("light.color"));
		pass->setUniform(id, mCurLight->getColor());

		id = pass->getUniformId(RAV_TXT("light.ambient"));
		pass->setUniform(id, mCurLight->getAmbient());
		
		id = pass->getUniformId(RAV_TXT("light.range"));
		pass->setUniform(id, mCurLight->getRange());

		id = pass->getUniformId(RAV_TXT("light.angle"));
		pass->setUniform(id, Ravage::Math::PI * mCurLight->getAngle() / 180.0f);
	
		id = pass->getUniformId(RAV_TXT("light.direction"));
		pass->setUniform(id, mCurLight->getDirection().normalize());

		id = pass->getUniformId(RAV_TXT("light.specular"));
		pass->setUniform(id, mCurLight->getSpecular());

		id = pass->getUniformId(RAV_TXT("depthBias"));
		pass->setUniform(id, 0.03f);

		if (mShadowScene)
		{
			id = pass->getUniformId(RAV_TXT("clipPlane"));
			pass->setUniform(id, Ravage::Vector2(0.03f, mCurLight->getRange()));
		}
		else
		{
			id = pass->getUniformId(RAV_TXT("lightClipPlane"));
			pass->setUniform(id, Ravage::Vector2(0.03f, mCurLight->getRange()));
		}

		if (mCurShader == &mParallaxShader)
		{
			id = pass->getUniformId(RAV_TXT("s_NormalMap"));
			pass->setUniform(id, mNormalTexture);

			id = pass->getUniformId(RAV_TXT("s_HeightMap"));
			pass->setUniform(id, mHeightTexture);
		}

		id = pass->getUniformId(RAV_TXT("m_WorldView"));
		pass->setUniform(id, worldView);

		id = pass->getUniformId(RAV_TXT("m_WorldMatrix"));
		pass->setUniform(id, world);

		id = pass->getUniformId(RAV_TXT("m_ViewMatrix"));
		pass->setUniform(id, view);

		id = pass->getUniformId(RAV_TXT("m_ProjectionMatrix"));
		pass->setUniform(id, proj);

		id = pass->getUniformId(RAV_TXT("m_WorldViewProj"));
		pass->setUniform(id, worldViewProj);

		id = pass->getUniformId(RAV_TXT("m_WorldViewInverse"));
		pass->setUniform(id, worldInv);

		id = pass->getUniformId(RAV_TXT("m_NormalMatrix"));
		pass->setUniform(id, normalMatrix);

		id = pass->getUniformId(RAV_TXT("m_LightViewProj"));
		pass->setUniform(id, lightViewProj);

		if (!mShadowScene)
		{
			id = pass->getUniformId(RAV_TXT("s_ShadowMap"));
			pass->setUniform(id, mShadowMap);

			id = pass->getUniformId(RAV_TXT("f_LBR"));
			pass->setUniform(id, 0.3f);
		}

		id = pass->getUniformId(RAV_TXT("v_EyePosition"));
		pass->setUniform(id, mMainCamera.getEyeVector());

		mRenderer->draw(obj.getDrawOperation());
		mCurShader->endPass();
	}

	mRenderer->unloadVertexData();
	return true;
}

bool Application::drawQuad(Ravage::Texture* src, Ravage::Texture* dest, int passId)
{
	mRenderer->beginScene(dynamic_cast<Ravage::RenderTexture*>(dest));

	Ravage::DrawOperation oper;
	oper.operationType = Ravage::DrawOperation::TYPE_TRIANGLE_LIST;
	oper.primitiveCount = 2;
	oper.startVertex = 0;

	mRenderer->loadVertexData(mQuadData);
	mCurShader->beginPass(passId);

	Ravage::ShaderPass* pass = mCurShader->getPass(passId);
	unsigned id = pass->getUniformId(RAV_TXT("source"));
	pass->setUniform(id, src);

	if (mCurShader == &mBlurShader)
	{
		id = pass->getUniformId(RAV_TXT("blurSamples"));
		pass->setUniform(id, 4.0f);
		
		id = pass->getUniformId(RAV_TXT("sigma"));
		pass->setUniform(id, 4.0f);
	}
	else if (mCurShader == &mDofShader)
	{
		id = pass->getUniformId(RAV_TXT("depthMap"));
		pass->setUniform(id, mDepthMap);

		id = pass->getUniformId(RAV_TXT("clipPlanes"));
		pass->setUniform(id, Vector2(mCurrentCamera->getClipPlanes()));
	}

	mRenderer->draw(&oper);
	mCurShader->endPass();

	mRenderer->unloadVertexData();
	mRenderer->endScene();
	return true;
}

void Application::renderScene()
{
	setShader(mDiffuseShader);
	setTransform(mTeapotTransform);
	drawMesh(mTeapot);

	setShader(mParallaxShader);
	setTransform(mPlaneTransform);
	drawMesh(mPlane);

	setShader(mCookTorranceShader);
	setTransform(mTeapotTransform2);
	drawMesh(mTeapot);
}

bool Application::run()
{
	if (!initialize())
		return false;

	if (!loadScene())
		return false;

	mTimer.reset();
	ShowCursor(FALSE);

	RECT cursorClip;
	GetClipCursor(&cursorClip);

	mPosX = (cursorClip.right + cursorClip.left) / 2;
	mPosY = (cursorClip.top + cursorClip.bottom) / 2;
	SetCursorPos(mPosX, mPosY);

	Ravage::DisplayWindow* window = mRenderCore->getDisplayWindow();
	while (window->keepAlive())
	{
		while ((mDelta = mTimer.getMilliseconds()) == 0)
			Ravage::Sleep(1);

		mTimer.reset();

		update();
		render();

	}

	return true;
}

void Application::update()
{
	Vector3 zaxis = (mCurrentCamera->getAtVector() - mCurrentCamera->getEyeVector()).normalize();
	Vector3 xaxis = Vector3::cross(zaxis, mCurrentCamera->getUpVector()).normalize();

	Ravage::Vector3 shift = Ravage::Vector3::ZERO;

	float speed = mDelta / 1000.0f;

	//mTeapotTransform.rotate(Vector3(speed, 0, 0));

	if (GetKeyState(VK_CONTROL) & 0x8000)
	{
		mCurrentCamera = &mLight1Camera;
		mCurrentAngles = &mLight1Angles;
	}
	else
	{
		mCurrentCamera = &mMainCamera;
		mCurrentAngles = &mMainAngles;
	}

	if (GetKeyState(0x50) & 0x8000) //P
		mUsePosteffects = true;
	else
		mUsePosteffects = false;

	if (GetKeyState(VK_SHIFT) & 0x8000)
		speed *= 10;

	if (GetKeyState(0x57) & 0x8000) //W
		mCurrentCamera->getTransform().translate(speed * zaxis);
	if (GetKeyState(0x53) & 0x8000) //S
		mCurrentCamera->getTransform().translate(-speed * zaxis);
	if (GetKeyState(0x41) & 0x8000) //A
		mCurrentCamera->getTransform().translate(-speed * xaxis);
	if (GetKeyState(0x44) & 0x8000) //D
		mCurrentCamera->getTransform().translate(speed * xaxis);

	POINT pos;
	GetCursorPos(&pos);

	int newX = mPosX, newY = mPosY;

	if (pos.x / (double) mPosX < 0.1)
	{
		newX = pos.x;
		pos.x = mPosX;
	}
	if (pos.y / (double) mPosY < 0.1)
	{
		newY = pos.y;
		pos.y = mPosY;
	}	

	SetCursorPos(newX, newY);
	
	Ravage::Vector2 angles(-(pos.x / (float)mPosX - 1), (pos.y / (float) mPosY- 1));

	*mCurrentAngles = *mCurrentAngles + 4 * angles;

	//mTeapotTransform.setLocalRotation(Vector3(0, mAngles.x, mAngles.y));
	mCurrentCamera->getTransform().setLocalRotation(Vector3(mCurrentAngles->y, mCurrentAngles->x, 0));
}

bool Application::setShader(Shader& shader)
{
	if (mShadowScene)
		mCurShader = &mShadowShader;
	else
		mCurShader = &shader;
	return true;
}

bool Application::setLight(Light& l)
{
	mCurLight = &l;
	return true;
}

bool Application::setTransform(Transform& t)
{
	mCurTransform = &t;
	return true;
}

struct IOMemory
{
	char* buffer;
	int size;
};

void png_user_read_data(png_structp png_ptr,
						png_bytep data, 
						png_size_t length)
{
	if (!png_ptr)
		return;

	IOMemory* buffer = static_cast<IOMemory*>(png_get_io_ptr(png_ptr));

	if (unsigned(buffer->size) < length)
		png_error(png_ptr, "Read error");

	memcpy(data, buffer->buffer, length);
		
	buffer->buffer += length;
	buffer->size -= length;
}

Ravage::Texture2D* Application::loadImage(const Ravage::String& filename)
{
	png_structp png_ptr  = 0;
	png_infop   info_ptr = 0;
		
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (!png_ptr)
	{
		//TODO: Log error.
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		//TODO: Log error.
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		//TODO: Log error.
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}

	Ravage::File file;
	if (!file.open(filename, Ravage::RAV_FMODE_READ))
		return 0;

	unsigned size = file.getSize();
	char* memory = new char[size];

	if (!file.read(memory, size))
		return 0;

	IOMemory buffer = {memory, size};
	png_set_read_fn(png_ptr, (png_voidp)&buffer, png_user_read_data);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, 0);

	delete[] memory;

	//TODO: Add support for this.
	if (png_get_bit_depth(png_ptr, info_ptr) != 8)
	{
		//TODO: Log error.
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}

	int bytes    = png_get_channels(png_ptr, info_ptr);
	Vector2 imageSize(png_get_image_height(png_ptr, info_ptr), png_get_image_width(png_ptr, info_ptr));

	png_bytepp row_ptrs = png_get_rows(png_ptr, info_ptr);

	Ravage::TextureFormat fmt;
	switch(bytes)
	{
	case 3:
		fmt = Ravage::TF_RGB24;
		break;
	default:
		return 0;
	}

	Ravage::Texture2D* tex = mRenderer->createTexture2D(imageSize, fmt);

	for (int row = 0; row < int(imageSize.y); row++)
		tex->setPixels((Ravage::Byte*)row_ptrs[row], int(imageSize.x) * (int(imageSize.y) - row - 1) * bytes, int(imageSize.x) * bytes);

	png_destroy_read_struct(&png_ptr, &info_ptr, 0);

	tex->apply();
	return tex;
}
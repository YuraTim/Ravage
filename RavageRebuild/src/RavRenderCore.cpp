#include "RavRenderCore.h"

namespace Ravage
{
	RenderCore::RenderCore() :
		mSettings(Settings::instance()),
		mRenderer(0),
		mDisplayWindow(0)
	{}

	RenderCore::~RenderCore()
	{
		if (mRenderer)
			shutdown();

		mSettings->freeInst();
	}

	bool RenderCore::initialize()
	{
		if (mRegisterMap.empty())
		{
			//TODO: Log error.
			return false;
		}

		String renderer = mSettings->getGraphicSettings()->getRenderer();
		RendererRegistrator registrator = 0;
		if (renderer.empty())
		{
			registrator = mRegisterMap.begin()->second;
			//TODO: Log.
		}
		else
		{
			std::map <String, RendererRegistrator>::iterator iter = mRegisterMap.find(renderer);

			if (iter == mRegisterMap.end())
			{
				//TODO: Log error.
				return false;
			}

			//TODO: Log.
			registrator = iter->second;
		}

		mRenderer = registrator();
		mDisplayWindow = mRenderer->initialize();

		if (!mDisplayWindow)
		{
			delete mRenderer;
			mRenderer = 0;
		}

		return mDisplayWindow != 0;
	}

	bool RenderCore::reinitialize()
	{
		if (!mRenderer)
		{
			//TODO: Log error.
			return false;
		}

		mDisplayWindow = mRenderer->reinitialize();
		return mDisplayWindow != 0;
	}

	void RenderCore::shutdown()
	{
		if (mRenderer)
		{
			mRenderer->shutdown();
			delete mRenderer;
			mRenderer = 0;
		}
	}
}
#ifndef RAVRENDERCORE_H_INCLUDED
#define RAVRENDERCORE_H_INCLUDED

//!!! TODO: Remove Cg from here due OpenGL ES doesn't support it!

#include "RavBase.h"
#include "RavMath.h"
#include "RavRenderer.h"
#include "RavDisplayWindow.h"

namespace Ravage
{
	class RenderCore : public Singleton<RenderCore>
	{
	public:
		typedef Renderer* (*RendererRegistrator)();

		RenderCore();
		~RenderCore();

		bool initialize();
		bool reinitialize();
		void shutdown();

		inline bool isNull() const
		{ return mRenderer == 0 || mDisplayWindow == 0; }

		inline void setWorldMatrix(const Matrix4& matrix)
		{ mWorldMatrix = matrix; }
		
		inline void setViewMatrix(const Matrix4& matrix)
		{ mViewMatrix = matrix; }

        inline void setProjectionMatrix(const Matrix4& matrix)
		{ mProjectionMatrix = matrix; }

        inline const Matrix4& getWorldMatrix() const
		{ return mWorldMatrix; }

        inline const Matrix4& getViewMatrix() const
		{ return mViewMatrix; }

        inline const Matrix4& getProjectionMatrix() const
		{ return mProjectionMatrix; }

		inline Matrix4 getWorldView() const
		{
			//TODO: Cache some results.
			return Matrix4::concatenate(mWorldMatrix, mViewMatrix);
		}

		inline Matrix4 getWorldViewProj() const
		{
			//TODO: Cache some results. For example in beginScene
			return Matrix4::concatenate(getWorldView(), mProjectionMatrix);
		}

		inline bool beginScene()
		{
			RavAssert(!isNull());
			return mRenderer->beginScene();
		}

		inline void endScene()
		{
			RavAssert(!isNull());
			return mRenderer->endScene();
		}

		inline void registerRenderer(String name, RendererRegistrator reg)
		{ mRegisterMap.insert(std::make_pair(name, reg)); }

		inline Renderer* getRenderer() const
		{ return mRenderer; }
		
		inline DisplayWindow* getDisplayWindow() const
		{ return mDisplayWindow; }
	private:
		Settings* mSettings;

		Renderer* mRenderer;
		DisplayWindow* mDisplayWindow;

		Matrix4 mWorldMatrix;
		Matrix4 mViewMatrix;
		Matrix4 mProjectionMatrix;

		std::map <String, RendererRegistrator> mRegisterMap;
	};
}

#endif /* RAVRENDERCORE_H_INCLUDED */
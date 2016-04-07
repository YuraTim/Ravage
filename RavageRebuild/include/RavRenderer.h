#ifndef RAVRENDERER_H_INCLUDED
#define RAVRENDERER_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"
#include "RavDisplayWindow.h"
#include "RavShader.h"
#include "RavShaderPass.h"
#include "RavVertexData.h"
#include "RavIndexData.h"
#include "RavVertexBuffer.h"
#include "RavIndexBuffer.h"
#include "RavRenderTexture.h"
#include "RavTexture2D.h"
#include "RavDrawOperation.h"
#include "RavGraphicEnum.h"
#include "RavListener.h"

namespace Ravage
{
	class Renderer
	{
	public:
		enum EventList
		{
			EVENT_ONDEVICELOST,
			EVENT_SIZE
		};

		virtual ~Renderer() = 0 {}

		virtual String getRendererName() = 0;

		virtual DisplayWindow* initialize() = 0;
		virtual DisplayWindow* reinitialize() = 0;
		virtual void shutdown() = 0;

		virtual bool beginScene(RenderTexture* target = 0) = 0;
		virtual void endScene() = 0;

		virtual bool loadShaderPass(ShaderPass* shader) = 0;
		virtual bool unloadShaderPass() = 0;

		virtual bool loadVertexData(VertexData* data) = 0;
		virtual bool unloadVertexData() = 0;

		virtual bool loadIndexData(IndexBuffer* data) = 0;
		virtual bool unloadIndexData() = 0;
		
		virtual bool clear(unsigned mask) = 0;

		virtual bool draw(DrawOperation* oper) = 0;

		virtual VertexBuffer* createVertexBuffer(unsigned size, 
												 GraphicResourceType type = GR_TYPE_DYNAMIC) = 0;
		virtual void release(VertexBuffer* buffer) = 0;

		virtual IndexBuffer* createIndexBuffer(unsigned size,
											   IndexBufferType type = IB_TYPE_16,
											   GraphicResourceType pool = GR_TYPE_DYNAMIC) = 0;
		virtual void release(IndexBuffer* buffer) = 0;

		virtual VertexData* createVertexData(VertexDeclaration* decl) = 0;
		virtual void release(VertexData* data) = 0;

		virtual ShaderPass* createShaderPass() = 0;
		virtual void release(ShaderPass* shader) = 0;

		virtual RenderTexture* createRenderTexture(const Vector2& size, RenderTextureFormat fmt, int depth) = 0;
		virtual void release(RenderTexture* texture) = 0;

		virtual Texture2D* createTexture2D(const Vector2& size, TextureFormat fmt) = 0;
		virtual void release(Texture2D* texture) = 0;

		virtual GraphicCoordSystem getCoordSystem() = 0;

		virtual bool setRenderState(RenderState state, int value) = 0;
		virtual bool setRenderState(RenderState state, const Color& value) = 0;
		virtual bool setRenderState(RenderState state, bool value) = 0;
		virtual bool setRenderState(RenderState state, Real value) = 0;

		//virtual int getRenderState(RenderState state) = 0;

		virtual Listener* getListener() = 0;
	};
}

#endif /* RAVRENDERER_H_INCLUDED */
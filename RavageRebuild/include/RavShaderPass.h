#ifndef RAVSHADERPASS_H_INCLUDED
#define RAVSHADERPASS_H_INCLUDED

//RENDERER SPECIFIC!
#include "RavBase.h"
#include "RavMath.h"
#include "RavColor.h"
#include "RavTexture.h"

namespace Ravage
{
	class ShaderPass
	{
	public:
		ShaderPass();
		virtual ~ShaderPass() = 0;

		virtual unsigned getUniformId(const String& name) = 0;

		virtual bool setUniform(unsigned id, const Matrix4& attrib) = 0;
		virtual bool setUniform(unsigned id, const Vector4& attrib) = 0;
		virtual bool setUniform(unsigned id, const Vector3& attrib) = 0;
		virtual bool setUniform(unsigned id, const Vector2& attrib) = 0;
		virtual bool setUniform(unsigned id, const Color& attrib) = 0;
		virtual bool setUniform(unsigned id, Real attrib) = 0;
		virtual bool setUniform(unsigned id, int attrib) = 0;
		virtual bool setUniform(unsigned id, Texture* attrib) = 0;

		virtual bool addSource(const String& source) = 0;
		virtual bool addSource(Byte* source, int size) = 0;

		virtual bool compile() = 0;

		inline void setSourceType(unsigned type)
		{ mSourceType = type; }

		inline void setVertexShaderOn(bool use)
		{ mUseVertexShader = use; }

		inline void setGeometryShaderOn(bool use)
		{ mUseGeometryShader = use; }

		inline void setPixelShaderOn(bool use)
		{ mUsePixelShader = use; }
	protected:
		unsigned mSourceType;

		bool mUseVertexShader;
		bool mUseGeometryShader;
		bool mUsePixelShader;
	};
}

#endif /* RAVSHADERPASS_H_INCLUDED */
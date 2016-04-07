#ifndef RAVSHADERPASSOPENGL_H_INCLUDED
#define RAVSHADERPASSOPENGL_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"
#include "RavShaderPass.h"

#include "OpenGL/RavLibrariesOpenGL.h"

namespace Ravage
{
	class ShaderPassOpenGL : public ShaderPass
	{
	public:
		ShaderPassOpenGL();
		virtual ~ShaderPassOpenGL();

		virtual bool addSource(const String& source);
		virtual bool addSource(Byte* source, int size);

		virtual bool compile();

		virtual unsigned getUniformId(const String& name);

		virtual bool setUniform(unsigned id, const Matrix4& attrib);
		virtual bool setUniform(unsigned id, const Vector4& attrib);
		virtual bool setUniform(unsigned id, const Vector3& attrib);
		virtual bool setUniform(unsigned id, const Vector2& attrib);
		virtual bool setUniform(unsigned id, const Color& attrib);
		virtual bool setUniform(unsigned id, Real attrib);
		virtual bool setUniform(unsigned id, int attrib);
		virtual bool setUniform(unsigned id, Texture* attrib);

		inline GLuint getProgram()
		{ return mProgram; }
	private:
		bool createShader(const char* presource, GLenum type);

		//NOT IMPLEMENTED:
		ShaderPassOpenGL(const ShaderPassOpenGL& pass);
		ShaderPassOpenGL& operator=(const ShaderPassOpenGL& pass);

		String mShaderSource;

		GLuint mProgram;

		GLuint mVertexShader;
		GLuint mGeometryShader;
		GLuint mPixelShader;

		int mCurrentSampler;
		std::map<unsigned, int> mSamplers;
	};
}

#endif /* RAVSHADEROPENGL_H_INLCUDED */
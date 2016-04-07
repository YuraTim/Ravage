#include "OpenGL/RavShaderPassOpenGL.h"
#include "OpenGL/RavRendererOpenGL.h"
#include "OpenGL/RavTextureOpenGL.h"

#include "RavStringUtils.h"

namespace Ravage
{
	const char* VERTEX_SHADER_PRESOURCE =
		"#version 330\n"
		"#define VERTEX_SHADER\n" //Vertex shader define
		"#define POSITION 0\n"    //ATTR0
		"#define POSITION0 0\n"
		"#define POSITION1 1\n"   //ATTR1
		"#define NORMAL 2\n"      //ATTR2
		"#define COLOR 3\n"       //ATTR3
		"#define COLOR0 3\n"
		"#define DIFFUSE 3\n"
		"#define COLOR1 4\n"      //ATTR4
		"#define SPECULAR 4\n"
		"#define FOGCOORD 5\n"    //ATTR5
		"#define TEXCOORD0 8\n"   //ATTR8
		"#define TEXCOORD1 9\n"   //ATTR9
		"#define TEXCOORD2 10\n"  //ATTR10
		"#define TEXCOORD3 11\n"  //ATTR11
		"#define TEXCOORD4 12\n"  //ATTR12
		"#define TEXCOORD5 13\n"  //ATTR13
		"#define TEXCOORD6 14\n"  //ATTR14
		"#define TEXCOORD7 15\n"; //ATTR15

	const char* GEOMETRY_SHADER_PRESOURCE = 
		"#version 330\n"
		"#define GEOMETRY_SHADER\n";
	
	const char* PIXEL_SHADER_PRESOURCE = 
		"#version 330\n"
		"#define PIXEL_SHADER\n";


	ShaderPassOpenGL::ShaderPassOpenGL() :
		mShaderSource(StringUtils::BLANK),
		mProgram(0),
		mVertexShader(0),
		mGeometryShader(0),
		mPixelShader(0),
		mCurrentSampler(0)
	{}

	ShaderPassOpenGL::~ShaderPassOpenGL()
	{
		if (mVertexShader)
		{
			glDeleteShader(mVertexShader);
			mVertexShader = 0;
		}

		if (mGeometryShader)
		{
			glDeleteShader(mGeometryShader);
			mGeometryShader = 0;
		}

		if (mPixelShader)
		{
			glDeleteShader(mPixelShader);
			mPixelShader = 0;
		}

		if (mProgram)
		{
			glDeleteProgram(mProgram);
			mProgram = 0;
		}
	}

	bool ShaderPassOpenGL::addSource(Byte* mem, int size)
	{
		//TODO: implement
		return false;
	}

	bool ShaderPassOpenGL::addSource(const String& source)
	{
		mShaderSource += RAV_TXT("\n") + source;
		return true;
	}

	bool ShaderPassOpenGL::compile()
	{
		mProgram = glCreateProgram();

		if (mUseVertexShader && !createShader(VERTEX_SHADER_PRESOURCE, GL_VERTEX_SHADER))
			return false;
		if (mUseGeometryShader && !createShader(GEOMETRY_SHADER_PRESOURCE, GL_GEOMETRY_SHADER))
			return false;
		if (mUsePixelShader && !createShader(PIXEL_SHADER_PRESOURCE, GL_FRAGMENT_SHADER))
			return false;

		GLint linked = 0;
		glLinkProgram(mProgram);
		glGetProgramiv(mProgram, GL_LINK_STATUS, &linked);

		if (!linked)
		{
			//TODO: Error log.
			GLint logsize = 0;
			glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logsize);

			char* buffer = new char[logsize];
			glGetProgramInfoLog(mProgram, logsize, 0, buffer);
			delete[] buffer;
			return false;
		}

		return true;
	}

	bool ShaderPassOpenGL::createShader(const char* presource, GLenum type)
	{
		char* source = StringUtils::newConvertA(mShaderSource);
		const GLchar* SOURCE[] = {presource, source};
		int LENGTH[] = {strlen(presource), strlen(source)};

		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 2, SOURCE, LENGTH);
		glCompileShader(shader);

		delete[] source;

		GLint compileStatus = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
		if (!compileStatus)
		{
			//TODO: Error log.
			GLint logsize = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);

			char* buffer = new char[logsize];
			glGetShaderInfoLog(shader, logsize, 0, buffer);
			delete[] buffer;

			return false;
		}

		switch (type)
		{
		case GL_VERTEX_SHADER:
			mVertexShader = shader;
			break;
		case GL_GEOMETRY_SHADER:
			mGeometryShader = shader;
			break;
		case GL_FRAGMENT_SHADER:
			mPixelShader = shader;
			break;
		}

		glAttachShader(mProgram, shader);
		return true;
	}

	unsigned ShaderPassOpenGL::getUniformId(const String& name)
	{
		char* buffer = StringUtils::newConvertA(name);
		int loc = glGetUniformLocation(mProgram, buffer);
		delete[] buffer;

		return *(unsigned*)(&loc);
	}

	bool ShaderPassOpenGL::setUniform(unsigned id, const Matrix4& attrib)
	{
		if (id == 0xFFFFFFFF)
			return false;

		glUniformMatrix4fv(id, 1, GL_TRUE, attrib.get());
		return true;
	}

	bool ShaderPassOpenGL::setUniform(unsigned id, const Vector4& attrib)
	{
		if (id == 0xFFFFFFFF)
			return false;

		glUniform4fv(id, 1, attrib.get());
		return true;
	}

	bool ShaderPassOpenGL::setUniform(unsigned id, const Color& attrib)
	{
		if (id == 0xFFFFFFFF)
			return false;

		glUniform4fv(id, 1, attrib.get());
		return true;
	}

	bool ShaderPassOpenGL::setUniform(unsigned id, const Vector3& attrib)
	{
		if (id == 0xFFFFFFFF)
			return false;

		glUniform3fv(id, 1, attrib.get());
		return true;
	}

	bool ShaderPassOpenGL::setUniform(unsigned id, const Vector2& attrib)
	{
		if (id == 0xFFFFFFFF)
			return false;

		glUniform2fv(id, 1, attrib.get());
		return true;
	}

	bool ShaderPassOpenGL::setUniform(unsigned id, Real attrib)
	{
		if (id == 0xFFFFFFFF)
			return false;

		glUniform1fv(id, 1, &attrib);
		return true;
	}

	bool ShaderPassOpenGL::setUniform(unsigned id, int attrib)
	{
		if (id == 0xFFFFFFFF)
			return false;

		glUniform1iv(id, 1, &attrib);
		return true;
	}

	bool ShaderPassOpenGL::setUniform(unsigned id, Texture* tex)
	{
		if (id == 0xFFFFFFFF)
			return false;

		std::map<unsigned, int>::iterator iter = mSamplers.find(id);

		int sampler = 0;

		if (iter == mSamplers.end())
		{
			sampler = mCurrentSampler;
			mSamplers.insert(std::make_pair(id, mCurrentSampler++));
		}
		else
			sampler = iter->second;

		TextureOpenGL* tog = dynamic_cast<TextureOpenGL*>(tex);
		if (!tog)
			return false;

		glActiveTexture(GL_TEXTURE0 + sampler);
		glBindTexture(tog->getTarget(), tog->getTextureId());
		glUniform1i(id, sampler);
		return true;
	}
}
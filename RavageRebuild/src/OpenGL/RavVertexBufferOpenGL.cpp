#include "OpenGL/RavVertexBufferOpenGL.h"

namespace Ravage
{
	VertexBufferOpenGL::VertexBufferOpenGL() :
		mBuffer(0),
		mSize(0),
		mType(GR_TYPE_DYNAMIC)
	{
		
	}

	VertexBufferOpenGL::~VertexBufferOpenGL()
	{
		glDeleteBuffers(1, &mBuffer);
		mBuffer = 0;
		mSize = 0;
	}

	bool VertexBufferOpenGL::create(unsigned size, GraphicResourceType type)
	{
		glGenBuffers(1, &mBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

		mType = type;
		setBuffer(0, size);
		return true;
	}

	void VertexBufferOpenGL::setBuffer(Byte* buffer, unsigned size)
	{
		//RavAssert(mBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

		GLenum hint = 0;
		switch (mType)
		{
		case GR_TYPE_STATIC:
			hint = GL_STATIC_DRAW;
			break;
		case GR_TYPE_DYNAMIC:
			hint = GL_DYNAMIC_DRAW;
			break;
		}
		glBufferData(GL_ARRAY_BUFFER, size, buffer, hint);
		mSize = size;
	}

	Byte* VertexBufferOpenGL::lock(unsigned offset, unsigned size, LockingFlag flag)
	{
		RavAssert(offset + size <= mSize);

		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

		GLenum access = 0;
		switch (flag)
		{
		case LOCK_WRITE:
			access = GL_WRITE_ONLY;
			break;
		case LOCK_READ_WRITE:
			access = GL_READ_WRITE;
			break;
		case LOCK_READ:
			access = GL_READ_ONLY;
			break;
		}

		return (Byte*)glMapBuffer(GL_ARRAY_BUFFER, access) + offset;
	}

	void VertexBufferOpenGL::unlock()
	{
		if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE)
		{
			//TODO: Raise data lose event.
		}
	}
}
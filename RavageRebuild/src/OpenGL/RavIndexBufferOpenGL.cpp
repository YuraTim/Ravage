#include "OpenGL\RavIndexBufferOpenGL.h"

namespace Ravage
{
	IndexBufferOpenGL::~IndexBufferOpenGL()
	{
		glDeleteBuffers(1, &mBuffer);
		mBuffer = 0;
		mSize = 0;
	}

	bool IndexBufferOpenGL::create(unsigned size, IndexBufferType type, GraphicResourceType pool)
	{
		glGenBuffers(1, &mBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);

		mType = type;
		mPool = pool;
		setBuffer(0, size);
		return true;
	}

	void IndexBufferOpenGL::setBuffer(Byte* buffer, unsigned size)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, hint);
		mSize = size;
	}

	Byte* IndexBufferOpenGL::lock(unsigned offset, unsigned size, LockingFlag flag)
	{
		RavAssert(offset + size <= mSize);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);

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

		return (Byte*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, access) + offset;
	}

	void IndexBufferOpenGL::unlock()
	{
		if (glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) == GL_FALSE)
		{
			//TODO: Raise data lose event.
		}
	}

	IndexBufferType IndexBufferOpenGL::getBufferType() const
	{ 
		return mType; 
	}
}
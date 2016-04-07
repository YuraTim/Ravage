#ifndef RAVVERTEXBUFFEROPENGL_H_INCLUDED
#define RAVVERTEXBUFFEROPENGL_H_INCLUDED

#include "OpenGL\RavLibrariesOpenGL.h"

#include "RavBase.h"
#include "RavVertexBuffer.h"

namespace Ravage
{
	class VertexBufferOpenGL : public VertexBuffer
	{
	public:
		VertexBufferOpenGL();
		virtual ~VertexBufferOpenGL();
		
		bool create(unsigned size, GraphicResourceType type);

		virtual void setBuffer(Byte* buffer, unsigned size);
		virtual Byte* lock(unsigned    offset = 0, 
						   unsigned    size = 0,
						   LockingFlag flag = LOCK_READ_WRITE);
		virtual void unlock();

		inline GLuint getBufferID() const
		{ return mBuffer; }
	private:
		GLuint mBuffer;
		unsigned mSize; 
		GraphicResourceType mType;
	};
}

#endif /* RAVVERTEXBUFFEROPENGL_H_INCLUDED */
#ifndef RAVINDEXBUFFEROPENGL_H_INCLUDED
#define RAVINDEXBUFFEROPENGL_H_INCLUDED

#include "RavBase.h"
#include "RavIndexBuffer.h"
#include "OpenGL\RavLibrariesOpenGL.h"

namespace Ravage
{
	class IndexBufferOpenGL : public IndexBuffer
	{
	public:
		virtual ~IndexBufferOpenGL();

		bool create(unsigned size, IndexBufferType type, GraphicResourceType pool);

		
		virtual void setBuffer(Byte* buffer, unsigned size);
		virtual Byte* lock(unsigned offset = 0, 
						   unsigned size = 0, 
						   LockingFlag flag = LOCK_READ_WRITE);
		virtual void unlock();
		virtual IndexBufferType getBufferType() const;

		inline GLuint getBufferID() const
		{ return mBuffer; }
	private:
		GLuint mBuffer;
		unsigned mSize;
		GraphicResourceType mPool;
		IndexBufferType mType;
	};
}

#endif /* RAVINDEXBUFFEROPENGL_H_INCLUDED */
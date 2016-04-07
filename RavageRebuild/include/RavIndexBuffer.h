#ifndef RAVINDEXBUFFER_H_INCLUDED
#define RAVINDEXBUFFER_H_INCLUDED

#include "RavGraphicEnum.h"

namespace Ravage
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = 0 {}

		virtual void setBuffer(Byte* buffer, unsigned size) = 0;
		virtual Byte* lock(unsigned offset = 0, 
						   unsigned size = 0, 
						   LockingFlag flag = LOCK_READ_WRITE) = 0;
		virtual void unlock() = 0;
		virtual IndexBufferType getBufferType() const = 0;
	};
}

#endif /* RAVINDEXBUFFER_H_INCLUDED */
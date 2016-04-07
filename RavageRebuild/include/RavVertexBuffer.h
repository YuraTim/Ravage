#ifndef RAVVERTEXBUFFER_H_INCLUDED
#define RAVVERTEXBUFFER_H_INCLUDED

#include "RavGraphicEnum.h"

namespace Ravage
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = 0 {}

		virtual void setBuffer(Byte* buffer, unsigned size) = 0;
		virtual Byte* lock(unsigned    offset = 0, 
						   unsigned    size = 0,
						   LockingFlag flag = LOCK_READ_WRITE) = 0;
		virtual void unlock() = 0;
	};
}

#endif /* RAVVERTEXBUFFER_H_INCLUDED */
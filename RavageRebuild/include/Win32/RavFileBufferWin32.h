#ifndef RAVFILEBUFFERWIN32_H_INCLUDED
#define RAVFILEBUFFERWIN32_H_INCLUDED

#include "RavDefines.h"

#if RAV_PLATFORM == RAV_PLATFORM_WIN32

#include <Windows.h>

#include "RavBase.h"
#include "RavFileModes.h"

namespace Ravage
{
	class FileBufferWin32
	{
	public:
		FileBufferWin32();
		~FileBufferWin32();

		bool open(const String& filename, unsigned mode);
		void close();

		int read(void* buffer, int size);
		int write(const void* buffer, int size);
		bool seek(int offset, FileSeekMode mode = RAV_SEEK_BEGIN);
		unsigned tell();

		bool setOffset(int offset);
		bool setSize(unsigned size);

		inline int getOffset() const
		{ return mOffset; }

		inline unsigned getSize() const
		{ return mSize; }
	private:
		HANDLE mFile;

		int mOffset;
		unsigned mSize;
	};
}

#endif /* RAV_PLATFORM */
#endif /* RAVFILEBUFFERWIN32_H_INCLUDED */
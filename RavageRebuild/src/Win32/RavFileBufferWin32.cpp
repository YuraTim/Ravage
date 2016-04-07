#if RAV_PLATFORM == RAV_PLATFORM_WIN32

#include "Win32/RavFileBufferWin32.h"

namespace Ravage
{
	FileBufferWin32::FileBufferWin32() :
		mFile(INVALID_HANDLE_VALUE),
		mOffset(0),
		mSize(0)
	{}

	FileBufferWin32::~FileBufferWin32()
	{
		if (mFile !=  INVALID_HANDLE_VALUE)
			close();
	}

	bool FileBufferWin32::open(const String& filename, unsigned mode)
	{
		DWORD resmode  = 0,
			  creation = 0;

		if (mode & RAV_FMODE_READ)
		{
			resmode  |= GENERIC_READ;
			creation = OPEN_EXISTING;
		}
		if (mode & RAV_FMODE_WRITE)
		{
			resmode |= GENERIC_WRITE;
			creation = OPEN_ALWAYS;
			//filename = 
		}

		mFile = CreateFile(filename.c_str(),
						   resmode,
						   FILE_SHARE_READ,
						   0,
						   creation,
						   FILE_ATTRIBUTE_NORMAL,
						   0);

		if (mFile != INVALID_HANDLE_VALUE)
		{
			DWORD hiword = 0;
			mSize = GetFileSize(mFile, &hiword);
			if (hiword)
			{
				//TODO: Error log.
				close();
				mSize = 0;
			}
		}

		return mFile != INVALID_HANDLE_VALUE;
	}

	void FileBufferWin32::close()
	{
		CloseHandle(mFile);
		mFile = 0;
	}

	int FileBufferWin32::read(void* buffer, int size)
	{
		//TODO: Size check.

		DWORD readed = 0;
		if (ReadFile(mFile, buffer, DWORD(size), &readed, 0) == 0)
		{
			//TODO: Error log.
			return -1;
		}
		return readed;
	}

	int FileBufferWin32::write(const void* buffer, int size)
	{
		DWORD writed = 0;
		if (WriteFile(mFile, buffer, DWORD(size), &writed, 0) == 0)
		{
			//TODO: Error log.
			return -1;
		}
		return writed;
	}

	bool FileBufferWin32::seek(int offset, FileSeekMode mode)
	{
		DWORD smode = 0;

		switch(mode)
		{
		case RAV_SEEK_BEGIN:
			smode = FILE_BEGIN;
			break;
		case RAV_SEEK_CUR:
			smode = FILE_CURRENT;
			break;
		case RAV_SEEK_END:
			smode = FILE_END;
			break;
		}

		if (SetFilePointer(mFile, LONG(offset) + LONG(mOffset), 0, smode) ==  INVALID_SET_FILE_POINTER)
		{
			//TODO: Error log.
			return false;
		}
		return true;
	}

	unsigned FileBufferWin32::tell()
	{
		return SetFilePointer(mFile, 0, 0, FILE_CURRENT);
	}

	bool FileBufferWin32::setOffset(int offset)
	{
		mOffset = offset;
		return seek(0);
	}

	bool FileBufferWin32::setSize(unsigned size)
	{
		mSize = size;
		return true;
	}
}

#endif /* RAV_PLATFORM */


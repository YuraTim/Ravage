#include "RavFile.h"

namespace Ravage
{
	const int RAV_FILE_MAX_BUFFER_SIZE = 1024;

	File::File() :
		mFileBuffer(0),
		mReadBuffer(0),
		mReadBufferOffset(0),
		mReadBufferSize(0),
		mFlags(0)
	{}

	File::~File()
	{
		if (isOpened())
			close();

		if (mReadBuffer)
			delete[] mReadBuffer;
	}

	bool File::open(const String& filename, unsigned mode)
	{
		if (isOpened())
			close();

		mFlags = 0;

		if (mode & RAV_FMODE_TEXT)
			mFlags |= RAV_FFLAG_TEXT;
		else
			mFlags |= RAV_FFLAG_BINARY;

		FileSystem* fsys = FileSystem::instance();
		mFileBuffer = fsys->openFileBuffer(filename, mode);
		fsys->freeInst();

		if (mFileBuffer)
		{
			mFlags |= RAV_FFLAG_OPENED;
			mFlags |= RAV_FFLAG_ANSI;

			if (mode & RAV_FMODE_READ)
			{
				if (!mReadBuffer)
					mReadBuffer = new Byte[RAV_FILE_MAX_BUFFER_SIZE];
				mReadBufferOffset = 0;
				mReadBufferSize   = 0;
			}
		}

		return mFileBuffer != 0;
	}

	void File::close()
	{
		FileSystem* fsys = FileSystem::instance();
		fsys->closeFileBuffer(mFileBuffer);
		fsys->freeInst();
	}

	bool File::read(void* buffer, int size, int count)
	{
		int realsize = size * count;
		
		if (realsize == 0)
			return true;
		else if (realsize < 0)
			return false;

		int rest = realsize;	
		while (rest > mReadBufferSize)
		{
			if (mReadBufferSize > 0)
			{
				memcpy((Byte*)buffer + realsize - rest, mReadBuffer + mReadBufferOffset, sizeof(Byte) * mReadBufferSize);
				rest -= mReadBufferSize;
			}
			
			mReadBufferOffset = 0;
			mReadBufferSize   = mFileBuffer->read(mReadBuffer, RAV_FILE_MAX_BUFFER_SIZE);
			
			if (mReadBufferSize == 0)
				mFlags |= RAV_FFLAG_END;

			if (mReadBufferSize < RAV_FILE_MAX_BUFFER_SIZE && 
				mReadBufferSize < rest)
				return false;

			int toread = rest;
			if (RAV_FILE_MAX_BUFFER_SIZE < toread)
				toread = RAV_FILE_MAX_BUFFER_SIZE;

			memcpy((Byte*)buffer + realsize - rest, mReadBuffer, sizeof(Byte) * toread);
			mReadBufferOffset += toread;
			mReadBufferSize   -= toread;
			rest -= toread;
		}

		if (rest > 0)
		{
			memcpy((Byte*)buffer + realsize - rest, mReadBuffer + mReadBufferOffset, sizeof(Byte) * rest);
			mReadBufferOffset += rest;
			mReadBufferSize   -= rest;
		}
		return true;
	}

	bool File::write(const void* buffer, int size, int count)
	{
		int realsize = size * count;
		
		if (realsize == 0)
			return true;
		else if (realsize < 0)
			return false;

		return mFileBuffer->write(buffer, realsize) == realsize;
	}

	bool File::seek(int offset, FileSeekMode mode)
	{
		RavAssert(mFileBuffer);
		return mFileBuffer->seek(offset, mode);
	}

	unsigned File::tell()
	{
		RavAssert(mFileBuffer);
		return mFileBuffer->tell();
	}
	
	bool File::readLine(String& dest, const String& endline)
	{
		dest.clear();
		Symbol cur = 0;
		do
		{
			cur = getSymbol();
			if (isEnd())
				break;

			dest.push_back(cur);
		}
		while(endline.find(cur) == String::npos);
		return true;
	}

	Symbol File::getSymbol()
	{
		//TODO: Unicode support.
		RavAssert(mFileBuffer);
		char sym = 0;
		read(&sym);

		if (sym == '\r')
			sym = '\n';

		return StringUtils::convert(sym);
	}

	unsigned File::getSize() const
	{
		RavAssert(mFileBuffer);
		return  mFileBuffer->getSize();
	}
}
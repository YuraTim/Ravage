#ifndef RAVFILE_H_INCLUDED
#define RAVFILE_H_INCLUDED

#include "RavBase.h"
#include "RavFileBuffer.h"
#include "RavFileSystem.h"
#include "RavStringUtils.h"
#include "RavFileModes.h"

namespace Ravage
{
	class File
	{
	public:
		File();
		~File();

		bool open(const String& filename, unsigned mode);
		void close();

		bool seek(int offset, FileSeekMode mode = RAV_SEEK_BEGIN);
		unsigned tell();

		bool read(void* data, int size, int count);
		bool write(const void* data, int size, int count);

		template<typename Type>
		inline bool read(Type* data, int count)
		{ return read(data, sizeof(Type), count); }

		template<typename Type>
		inline bool read(Type* data)
		{ return read(data, 1); }

		template<typename Type>
		inline bool write(const Type* data, int count)
		{ return write(data, sizeof(Type), count); }

		template<typename Type>
		inline bool write(const Type* data)
		{ return write(data, 1); }

		bool readLine(String& dest, const String& endline);
		bool writeLine(const String& from);
		
		Symbol getSymbol();
		
		unsigned getSize() const;

		inline bool isOpened() const
		{ return (mFlags & RAV_FFLAG_OPENED) != 0; }

		inline bool isEnd() const
		{ return (mFlags & RAV_FFLAG_END) != 0; }

		inline bool isTextMode() const
		{ return (mFlags & RAV_FFLAG_TEXT) != 0; }

		inline bool isBinaryMode() const
		{ return (mFlags & RAV_FFLAG_BINARY) != 0; }

		inline bool isAnsiMode() const
		{ return (mFlags & RAV_FFLAG_ANSI) != 0; }

		inline bool isUnicodeMode() const
		{ return (mFlags & RAV_FFLAG_ANSI) == 0; }
	private:
		FileBuffer* mFileBuffer;
		Byte*    mReadBuffer;
		int      mReadBufferOffset;
		int      mReadBufferSize;
		unsigned mFlags;
	};
}

#endif /* RAVFILE_H_INCLUDED */
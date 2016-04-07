#ifndef RAVFILESYSTEM_H_INCLUDED
#define RAVFILESYSTEM_H_INCLUDED

#include "RavBase.h"
#include "RavArcStructs.h"
#include "RavFileBuffer.h"

namespace Ravage
{
	class FileSystem : public Singleton<FileSystem>
	{
	public:
		FileSystem();
		~FileSystem();

		bool initialize();
		void shutdown();

		void addDirectory(const String& dir);
		void addArchive(const String& arcname);

		void addArcEntry(unsigned arcid, const ArcEntry* entry, int count);
		void addArcAttribute(unsigned arcid, const ArcAttribute* attr, int count);

		FileBuffer* openFileBuffer(const String& filename, unsigned mode);
		void closeFileBuffer(FileBuffer* file);
	private:
		struct Archive
		{
			ArcHeader header;
			std::vector<ArcEntry> entries;
			std::vector<ArcAttribute> attributes;
		};

		List<FileBuffer> mFileBuffers;

		std::vector<Archive> mArchives;
		std::vector<String>  mPath;
	};
}

#endif /* RAVFILESYSTEM_H_INCLUDED */
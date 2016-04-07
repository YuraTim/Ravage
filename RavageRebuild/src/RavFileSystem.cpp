#include "RavFileSystem.h"
#include "RavFileUtils.h"

namespace Ravage
{
	FileSystem::FileSystem()
	{}

	FileSystem::~FileSystem()
	{}

	bool FileSystem::initialize()
	{
		addDirectory(FileUtils::getEngineFolder());
		return true;
	}

	void FileSystem::shutdown()
	{
		List<FileBuffer>* cur = mFileBuffers.next;

		while (cur)
		{
			List<FileBuffer>* next = cur->next;
			cur->data.close();
			delete cur;
			cur = next;
		}
	}

	void FileSystem::addDirectory(const String& dir)
	{
		mPath.push_back(dir);
	}

	FileBuffer* FileSystem::openFileBuffer(const String& filename, unsigned mode)
	{
		List<FileBuffer>* newel = new List<FileBuffer>;
		FileBuffer* res = &(newel->data);

		bool opened = false;

		//Add archive search.

		for (std::vector<String>::const_iterator iter = mPath.begin(); iter != mPath.end(); ++iter)
		{
			String path = (*iter) + RAV_PATH_DELIM + filename;
			if (res->open(path, mode))
			{
				opened = true;
				break;
			}
		}

		if (!opened)
		{
			//TODO: Error log.
			delete newel;
			return 0;
		}

		newel->next = mFileBuffers.next;
		newel->prev = &(mFileBuffers);

		if (mFileBuffers.next)
			mFileBuffers.next->prev = newel;
		mFileBuffers.next = newel;

		return res;
	}

	void FileSystem::closeFileBuffer(FileBuffer* fb)
	{
		List<FileBuffer>* cur = mFileBuffers.next; 
		while (cur)
		{
			if (&(cur->data) == fb)
			{
				fb->close();
				cur->remove();
				delete cur;
				return;
			}
		}
	}
}
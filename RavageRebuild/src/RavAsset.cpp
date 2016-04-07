#include "RavAsset.h"

namespace Ravage
{
	Asset::~Asset()
	{}

	bool Asset::load(File& file)
	{
		int size = file.getSize();
		Byte* buffer = new Byte[size];
		
		file.read(buffer, size);

		bool result = load(buffer, size);
		
		delete[] buffer;
		return result;
	}

	bool Asset::load(const String& filename)
	{
		File file;
		
		if (!file.open(filename, RAV_FMODE_READ))
		{
			//TODO: Error log.
			return false;
		}

		return load(file);
	}
}
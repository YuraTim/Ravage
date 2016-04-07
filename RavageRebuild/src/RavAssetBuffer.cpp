#include "RavAssetBuffer.h"

namespace Ravage
{
	AssetBuffer::AssetBuffer() :
		mBuffer(0),
		mBufferSize(0)
	{}

	AssetBuffer::~AssetBuffer()
	{
		releaseBuffer();
	}

	bool AssetBuffer::load(Byte* buffer, int size)
	{
		releaseBuffer();

		mBuffer = new Byte[size];
		memcpy(mBuffer, buffer, sizeof(Byte) * size);
		mBufferSize = size;
		return true;
	}

	bool AssetBuffer::load(File& file)
	{
		unsigned size = file.getSize();
		
		//TODO: Remove additional buffer.
		Byte* buffer = new Byte[size];
		file.read(buffer, size);

		bool result = load(buffer, size);
		delete[] buffer;

		return result;
	}

	bool AssetBuffer::load(const String& filename)
	{
		File file;
		file.open(filename, RAV_FMODE_READ);
		return load(file);
	}

	void AssetBuffer::releaseBuffer()
	{
		if (mBuffer)
			delete[] mBuffer;

		mBuffer = 0;
		mBufferSize = 0;
	}
}
#ifndef RAVASSETBUFFER_H_INCLUDED
#define RAVASSETBUFFER_H_INCLUDED

#include "RavBase.h"
#include "RavAsset.h"

namespace Ravage
{
	class AssetBuffer : public Asset
	{
	public:
		AssetBuffer();
		virtual ~AssetBuffer();

		virtual bool load(Byte* memory, int size);
		virtual bool load(File& file);
		virtual bool load(const String& filename);

		void releaseBuffer();
	protected:
		Byte* mBuffer;
		int   mBufferSize;
	};
}

#endif /* RAVASSETBUFFER_H_INCLUDED */
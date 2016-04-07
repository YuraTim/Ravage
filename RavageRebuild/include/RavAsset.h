#ifndef RAVASSET_H_INCLUDED
#define RAVASSET_H_INCLUDED

#include "RavBase.h"
#include "RavFile.h"

namespace Ravage
{
	class Asset
	{
	public:
		virtual ~Asset() = 0;

		virtual bool load(Byte* memory, int size) = 0;
		virtual bool load(File& file);
		virtual bool load(const String& filename);
	};
}

#endif /* RAVASSET_H_INCLUDED */
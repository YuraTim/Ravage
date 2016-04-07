#include "RavVertexDeclaration.h"

namespace Ravage
{
	void VertexDeclaration::addElement(const VertexDeclaration::Element& el)
	{
		if (mElements.size() <= el.stream)
			mElements.resize(el.stream + 1);

		mElements.at(el.stream).push_back(el);
	}

	unsigned VertexDeclaration::getStreamVertexSize(ushort streamIdx) const
	{
		unsigned result = 0;

		if (mElements.size() <= streamIdx)
			return 0;

		std::vector<std::vector<Element> >::const_iterator stream = mElements.begin() + streamIdx;
		for (std::vector<Element>::const_iterator iter = stream->begin(); iter != stream->end(); ++iter)
			result += getTypeSize(iter->type);

		return result;
	}

	unsigned VertexDeclaration::getTypeSize(VertexDeclaration::ElementType type) const
	{
		switch (type)
		{
		case TYPE_REAL1:
			return sizeof(Real);
		case TYPE_REAL2:
			return 2 * sizeof(Real);
		case TYPE_REAL3:
			return 3 * sizeof(Real);
		case TYPE_REAL4:
			return 4 * sizeof(Real);
		case TYPE_BYTE3:
			return 3 * sizeof(Byte);
		case TYPE_BYTE4:
			return 4 * sizeof(Byte);
		}
		return 0;
	}
}
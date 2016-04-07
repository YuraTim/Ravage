#include "RavVertexData.h"

namespace Ravage
{
	VertexData::VertexData(VertexDeclaration* decl) :
		mListener(VertexData::EVENT_SIZE),
		mVertexDeclaration(decl)
	{}

	VertexData::~VertexData()
	{}
}
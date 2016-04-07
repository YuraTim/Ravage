#ifndef RAVDRAWOPERATION_H_INCLUDED
#define RAVDRAWOPERATION_H_INCLUDED

#include "RavBase.h"

namespace Ravage
{
	struct DrawOperation
	{
		enum Type
		{
			TYPE_POINT_LIST,
			TYPE_LINE_LIST,
			TYPE_LINE_STRIP,
			TYPE_TRIANGLE_LIST,
			TYPE_TRIANGLE_STRIP,
			TYPE_TRIANGLE_FAN
		};

		Type operationType;

		unsigned primitiveCount;

		unsigned startIndex;
		unsigned startVertex;
	};
}

#endif /* RAVDRAWOPERATION_H_INCLUDED */
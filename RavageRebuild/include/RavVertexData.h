#ifndef RAVVERTEXDATA_H_INCLUDED
#define RAVVERTEXDATA_H_INCLUDED

#include "RavBase.h"
#include "RavListener.h"
#include "RavVertexBuffer.h"
#include "RavVertexDeclaration.h"

namespace Ravage
{
	class VertexData
	{
	public:
		enum EventList
		{
			EVENT_ONDATALOST,
			EVENT_SIZE
		};

		VertexData(VertexDeclaration* decl);
		virtual ~VertexData();

		virtual bool generateStreamInfo() = 0;

		inline VertexDeclaration* getDeclaration()
		{ return mVertexDeclaration; }

		inline void addStream(VertexBuffer* stream)
		{ mStreams.push_back(stream); }

		inline ushort getStreamCount() const
		{ return mStreams.size(); }

		inline void setStream(ushort streamIdx, VertexBuffer* stream)
		{
			while (mStreams.size() <= streamIdx)
				addStream(0);
			mStreams.at(streamIdx) = stream;
		}

		inline VertexBuffer* getStream(ushort streamIdx) const
		{ return mStreams.at(streamIdx); }

	private:
		Listener mListener;

		VertexDeclaration* mVertexDeclaration;

		//TODO: Remove vector
		std::vector<VertexBuffer*> mStreams;
	};
}

#endif /* RAVINDEXDATA_H_INCLUDED */
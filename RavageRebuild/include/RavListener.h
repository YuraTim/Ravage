#ifndef RAVLISTENER_H_INCLUDED
#define RAVLISTENER_H_INCLUDED

#include "RavBase.h"
#include "RavEvent.h"

namespace Ravage
{
	class Listener
	{
	public:

		inline Listener(int size)
		{ mEventList.resize(size); }

		inline void raiseEvent(int code, EventData* data = 0)
		{ mEventList.at(code).invoke(data); }

		inline void addHandler(int code, const Event::Handler handler, void* userdata = 0)
		{ mEventList.at(code).addHandler(handler, userdata); }

		inline void remove(void* userdata)
		{ for (Events::iterator i = mEventList.begin(); i != mEventList.end(); ++i) i->remove(userdata); }
	private:
		//TODO: Remove vectore
		typedef std::vector<Event> Events;
		
		Events mEventList;
	};
}

#endif /* RAVLISTENER_H_INCLUDED */
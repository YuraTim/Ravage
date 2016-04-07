#ifndef RAVEVENT_H_INCLUDED
#define RAVEVENT_H_INCLUDED

#include "RavBase.h"

namespace Ravage
{
	class Event;

	struct EventData
	{
		Event* base;
	};

    class Event
    {
        public:
            typedef void (*Handler)(EventData* data, void* userdata);

            void invoke(EventData* data);
			void remove(void* userdata);

			inline void addHandler(const Handler handler, void* userdata = 0)
			{ mFunctions.push_back(std::make_pair(handler, userdata)); }
        private:
            EventData* mEventData;

			//TODO: vector replace
			std::vector<std::pair<Handler, void*>> mFunctions;
    };
}

#endif // RAVEVENT_H_INCLUDED

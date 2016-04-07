#include "RavEvent.h"

namespace Ravage
{
	void Event::invoke(EventData* data)
	{
		if (data)
			data->base = this;

		for(std::vector<std::pair<Handler, void*> >::const_iterator i = mFunctions.begin(); 
			i != mFunctions.end(); ++i)
			(i->first)(data, i->second);
	}

	void Event::remove(void* userdata)
	{
		for(std::vector<std::pair<Handler, void*> >::const_iterator i = mFunctions.begin(); 
			i != mFunctions.end(); ++i)
			if (i->second == userdata)
			{
				mFunctions.erase(i);
				i = mFunctions.begin();
			}
	}
}
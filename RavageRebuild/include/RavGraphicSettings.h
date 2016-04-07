#ifndef RAVGRAPHICSETTINGS_H_INCLUDED
#define RAVGRAPHICSETTINGS_H_INCLUDED

#include "RavBase.h"

namespace Ravage
{
	class GraphicSettings
	{
	public:
		GraphicSettings();

		inline String getRenderer() const
		{ return mRenderer; }

		inline void setRenderer(const String& renderer)
		{ mRenderer = renderer; }
	private:
		String mRenderer;
	};
}

#endif /* RAVGRAPHICSETTINGS_H_INCLUDED */
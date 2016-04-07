#ifndef RAVRENDERABLE_H_INCLUDED
#define RAVRENDERABLE_H_INCLUDED

#include "RavBase.h"
#include "RavComponent.h"
#include "RavMaterial.h"
#include "RavListener.h"

namespace Ravage
{
	class Renderable : public Component
	{
	public:
		enum EventList
		{
			EVENT_ONSHADERCHANGE,
			EVENT_SIZE
		};

		Renderable();
		~Renderable();

		virtual bool render() = 0;

		inline bool IsEnabled() const
		{ return mEnabled; }
		
		inline Material* getMaterial() const
		{ return mMaterial; }

		inline bool castShadows() const
		{ return mCastShadows; }

		inline bool receiveShadows() const
		{ return mReceiveShadows; }
		
		void setMaterial(Material* material);

		inline void setEnableFlag(bool enable)
		{ mEnabled = enable; }

		inline void setReceiveShadowsFlag(bool flag)
		{ mReceiveShadows = flag; }

		inline void setCastShadowsFlag(bool flag)
		{ mCastShadows = flag; }

		inline const Listener* getListener() const
		{ return &mListener; }

	protected:
		static void onShaderChange(EventData*, void* data);

		Listener mListener;

		bool mEnabled;
		bool mCastShadows;
		bool mReceiveShadows;

		Material* mMaterial;
	};
}

#endif /* RAVRENDERABLE_H_INCLUDED */
#include "RavRenderable.h"

namespace Ravage
{
	Renderable::Renderable() :
		mListener(EVENT_SIZE),
		mEnabled(true),
		mCastShadows(true),
		mReceiveShadows(true),
		mMaterial(0)
	{}

	Renderable::~Renderable()
	{
		setMaterial(0);
	}

	void Renderable::setMaterial(Material* mat)
	{
		if (mMaterial)
			mMaterial->getListener()->remove(this);

		mMaterial = mat;

		if (mat)
			mMaterial->getListener()->addHandler(Material::EVENT_ONSHADERCHANGED, onShaderChange, this);
	}

	void Renderable::onShaderChange(EventData*, void* data)
	{
		Renderable* renderable = (Renderable*)data;
		renderable->mListener.raiseEvent(EVENT_ONSHADERCHANGE);
	}


}
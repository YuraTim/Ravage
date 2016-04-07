#ifndef RAVLIGHT_H_INCLUDED
#define RAVLIGHT_H_INCLUDED

namespace Ravage
{
	class Light
	{
	public:
		enum LightType
		{
			TYPE_SPOT,
			TYPE_DIRECTIONAL,
			TYPE_POINT
		};

		enum ShadowType
		{
			SHADOW_HARD,
			SHADOW_SOFT,
			SHADOW_NONE
		};

		Light();
		~Light();

		inline LightType getType()
		{ return mType; }

		inline ShadowType getShadowType()
		{ return mShadowType; }
	private:
		LightType  mType;
		ShadowType mShadowType;
	};
}

#endif /* RAVLIGHT_H_INCLUDED */
#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "RavTransform.h"
#include "RavMath.h"
#include "RavColor.h"

using Ravage::Real;
using Ravage::Vector3;
using Ravage::Color;
using Ravage::Transform;

class Light
{
public:
	Light(Real spotAngle = 90.0f, Real range = 30.0f,
		  Real ambient = 0.1, 
		  const Color& diffuse = Color(0.5f, 0.5f, 0.0f, 1.0f),
		  const Color& specular = Color(1.0f, 1.0f, 1.0f, 1.0f)) :
		mSpotAngle(spotAngle),
		mRange(range),
		mAmbient(ambient),
		mColor(diffuse),
		mSpecular(specular)
	{}

	inline Color getColor() const
	{ return mColor; }

	inline Real getAmbient() const
	{ return mAmbient; }

	inline Transform& getTransform()
	{ return mTransform; }

	inline const Transform& getTransform() const
	{ return mTransform; }

	inline Real getAngle() const
	{ return mSpotAngle; }

	inline Real getRange() const
	{ return mRange; }

	inline Vector3 getDirection() const
	{
		const Matrix4& w = mTransform.getWorldMatrix();
		return Vector3(w.m[2][0], w.m[2][1], w.m[2][2]);
	}

	inline Color getSpecular() const
	{ return mSpecular; }
private:
	Transform mTransform;

	Real mSpotAngle;
	Real mRange;
	Real mAmbient;
	Color mColor;
	Color mSpecular;
};

#endif /* LIGHT_H_INCLUDED */
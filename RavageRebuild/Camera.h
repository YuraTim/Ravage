#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"
#include "RavTransform.h"

using Ravage::Real;
using Ravage::Matrix4;
using Ravage::Vector3;

class Camera
{
public:
	Camera(Real fovy = Real(60), 
		   Real aspect = Real(16.0 / 9.0), 
		   Real zn = Real(0.3), 
		   Real zf = Real(100)) :
		mFovy(fovy),
		mAspect(aspect),
		mZn(zn),
		mZf(zf)
	{}

	inline Vector3 getEyeVector() const
	{ 
		const Matrix4& w = mTransform.getWorldMatrix();
		return Vector3(w.m[3][0], w.m[3][1], w.m[3][2]); 
	}

	inline Vector3 getAtVector() const
	{ 
		const Matrix4& w = mTransform.getWorldMatrix();
		return Vector3(w.m[2][0] + w.m[3][0], w.m[2][1] + w.m[3][1], w.m[2][2] + w.m[3][2]); 
	}

	inline Vector3 getUpVector() const
	{ 
		const Matrix4& w = mTransform.getWorldMatrix();
		return Vector3(w.m[1][0], w.m[1][1], w.m[1][2]); 
	}

	inline Vector3 getRightVector() const
	{
		const Matrix4& w = mTransform.getWorldMatrix();
		return Vector3(w.m[0][0], w.m[0][1], w.m[0][2]); 
	}

	inline Matrix4 getViewMatrix() const
	{
		Matrix4 w = mTransform.getWorldMatrix();
		
		Vector3 eye = getEyeVector();
		Vector3 at  = getAtVector();
		Vector3 up  = getUpVector();
		
		return Ravage::createMatrixLookAtRH(w, eye, at, up);
	}

	inline Matrix4 getProjectionMatrix() const
	{
		Matrix4 result;
		return Ravage::createMatrixPerspectiveFovRH(result, Ravage::Math::PI * mFovy / 180, mAspect, mZn, mZf);
	}

	inline Ravage::Transform& getTransform()
	{ return mTransform; }

	inline void setAspect(Real aspect)
	{ mAspect = aspect; }

	inline Ravage::Vector2 getClipPlanes() const
	{ return Ravage::Vector2(mZn, mZf); }

private:
	Real mFovy;
	Real mAspect;
	Real mZn;
	Real mZf;

	Ravage::Transform mTransform;
};

#endif /* CAMERA_H_INCLUDED */
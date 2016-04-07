#ifndef RAVTRANSFORM_H_INCLUDED
#define RAVTRANSFORM_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"

namespace Ravage
{
	//TODO: Parent - child relationship
	class Transform
	{
	public:
		enum Space
		{
			SPACE_SELF,
			SPACE_WORLD
		};
		
		inline Transform() :
			mWorldMatrix(Matrix4::IDENTITY),
			mPosition(Vector3::ZERO),
			mRotation(Vector3::ZERO),
			mScale(Vector3::IDENTITY),
			mUpdate(false)	
		{}


		inline const Vector3& getLocalPosition() const
		{ return mPosition; }

		inline Vector3 getPosition()
		{
			/*if (mParent)
				return mParent->getPosition() + mPosition; //!!!SCALE*/
			return mPosition;
		}

		inline const Quaternion& getLocalRotation() const
		{ return mRotation; }

		inline Quaternion getRotation() const
		{
			/*if (mParent)
				return Quaternion::multiply(mParent->getRotation(), mRotation).normalize();*/
			return mRotation;
		}

		inline const Vector3& getLocalScale() const
		{ return mScale; }

		inline void setLocalPosition(const Vector3& pos)
		{ 
			mPosition = pos; 
		}

		inline void setLocalRotation(const Quaternion& rot)
		{ 
			mUpdate = true;
			(mRotation = rot).normalize(); 
		}

		inline void setLocalRotation(const Vector3& axis, Real angle)
		{ 
			mUpdate = true;
			mRotation = Quaternion(axis, angle); 
		}

		inline void setLocalRotation(const Vector3& angles)
		{ 
			mUpdate = true;
			mRotation = Quaternion(angles); 
		}

		inline void setLocalScale(const Vector3& scale)
		{ 
			mUpdate = true;
			mScale = scale; 
		}

		inline void rotate(const Vector3& rotation, Space space = SPACE_SELF)
		{
			mUpdate = true;
			mRotation = Quaternion::multiply(mRotation, Quaternion(rotation)).normalize();
		}

		inline void rotateAround(const Vector3& axis, Real angle, Space space = SPACE_SELF)
		{
			mUpdate = true;
			mRotation = Quaternion::multiply(mRotation, Quaternion(axis, angle)).normalize();
		}

		inline void translate(const Vector3& shift, Space space = SPACE_SELF)
		{
			mUpdate = true;
			mPosition += shift;
		}

		inline const Matrix4& getWorldMatrix() const
		{
			if (mUpdate)
			{
				Matrix4 trans, rot, scale;
				createMatrixTranslation(trans, mPosition);
				createMatrixScaling(scale, mScale);
				createMatrixRotation(rot, mRotation);
				mWorldMatrix = Matrix4::concatenate(scale, Matrix4::concatenate(rot, trans));
				mUpdate = false;
			}
			return mWorldMatrix;
		}

	private:
		//TODO: mutable works for Android?
		mutable Matrix4 mWorldMatrix;

		Vector3 mPosition;
		Quaternion mRotation;
		Vector3 mScale;

		mutable bool mUpdate;

		Transform* mParent;
	};
}

#endif /* RAVTRANSFORM_H_INCLUDED */
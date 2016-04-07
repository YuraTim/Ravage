#ifndef RAVMATHQUATERNION_H_INCLUDED
#define RAVMATHQUATERNION_H_INCLUDED

#include "RavMathBase.h"
#include "RavMathVector3.h"

namespace Ravage
{
	class Quaternion
	{
	public:
		inline Quaternion()
		{}

		inline Quaternion(Real fw, Real fx, Real fy, Real fz) :
			w(fw), v(fx, fy, fz) 
		{}

		inline Quaternion(const Real* q) :
			w(q[0]), v(q[1], q[2], q[3])
		{}

		inline Quaternion(const Vector3& axis, Real angle)
		{
			Vector3 naxis = axis;
			naxis.normalize();

			Real s = Math::sin(angle / 2);
			w = Math::cos(angle / 2);
			v.x = s * naxis.x;
			v.y = s * naxis.y;
			v.z = s * naxis.z;

		}

		inline Quaternion(const Vector3& angles)
		{
			Real cx = Math::cos(angles.x / Real(2.0)), sx = Math::sin(angles.x / Real(2.0));
			Real cy = Math::cos(angles.y / Real(2.0)), sy = Math::sin(angles.y / Real(2.0));
			Real cz = Math::cos(angles.z / Real(2.0)), sz = Math::sin(angles.z / Real(2.0));

			w = cx * cy * cz + sx * sy * sz;
			v.x = sx * cy * cz - cx * sy * sz;
			v.y = cx * sy * cz + sx * cy * sz;
			v.z = cx * cy * sz - sx * sy * cz;
		}

		inline Real magnitudeSqr()
		{ return w * w + v.magnitudeSqr(); }

		inline Real magnitude()
		{ return Math::sqrt(magnitudeSqr()); }

		inline Quaternion& normalize()
		{
			Real length = magnitude();

			if (length > Real(0.0))
			{
				Real invLength = Real(1.0) / length;

				w *= invLength;
				v *= invLength;
			}
			return *this;
		}

		static inline Quaternion multiply(const Quaternion& q1, const Quaternion& q2)
		{
			Quaternion result;
			result.w = q1.w * q2.w - Vector3::dot(q1.v, q2.v);
			result.v = q1.w * q2.v + q2.w * q1.v + Vector3::cross(q1.v, q2.v);
			return result;
		}
	public:
		Real w;
		Vector3 v;
	};
}

#endif /* RAVMATHQUATERNION_H_INCLUDED */
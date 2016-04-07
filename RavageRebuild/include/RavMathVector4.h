#ifndef RAVMATHVECTOR4_H_INCLUDED
#define RAVMATHVECTOR4_H_INCLUDED

/* PART OF RAVAGE BASE */

#include "RavMathBase.h"
#include "RavMathVector2.h"
#include "RavMathVector3.h"

namespace Ravage
{
	class Vector4
	{
	public:
		inline Vector4()
		{}

		inline Vector4(Real fx, Real fy, Real fz, Real fw) :
			x(fx), y(fy), z(fz), w(fw)
		{}

		inline Vector4(const Vector2& vec) :
			x(vec.x), y(vec.y), z(Real(0)), w(Real(1))
		{}

		inline Vector4(const Vector3& vec) :
			x(vec.x), y(vec.y), z(vec.z), w(Real(1))
		{}
		
		inline explicit Vector4(const Real coords[4]) :
			x(coords[0]), y(coords[1]), z(coords[2]), w(coords[3])
		{}

		inline explicit Vector4(Real* const coords) :
			x(coords[0]), y(coords[1]), z(coords[2]), w(coords[3])
		{}

		inline explicit Vector4(Real scalar) :
			x(scalar), y(scalar), z(scalar), w(Real(1))
		{}

		inline Vector4& operator += (const Vector4& v)
		{
			x = v.w * x + w * v.x;
			y = v.w * y + w * v.y;
			z = v.w * z + w * v.z;
			w *= v.w;
		}

		inline Vector4& operator -= (const Vector4& v)
		{
			x = v.w * x - w * v.x;
			y = v.w * y - w * v.y;
			z = v.w * z - w * v.z;
			w *= v.w;
		}

		inline Real* get()
		{ return &x; }

		inline const Real* get() const
		{ return &x; }

		inline operator Vector3()
		{ return Vector3(x / w, y / w, z / w); }

	public:
		Real x, y, z, w;
	};
}

#endif /* RAVMATHVECTOR4_H_INCLUDED */
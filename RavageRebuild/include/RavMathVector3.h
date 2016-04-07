#ifndef RAVMATHVECTOR3_H_INCLUDED
#define RAVMATHVECTOR3_H_INCLUDED

/* PART OF RAVAGE BASE */

#include "RavMathBase.h"
#include "RavMathVector2.h"

namespace Ravage
{
	class Vector3
	{
	public:
		inline Vector3()
		{}

		inline Vector3(Real fx, Real fy, Real fz) :
			x(fx), y(fy), z(fz)
		{}
		
		inline Vector3(const Vector2& vec, Real fz = Real(0.0)) :
			x(vec.x), y(vec.y), z(fz)
		{}

		inline explicit Vector3(const Real coords[3]) :
			x(coords[0]), y(coords[1]), z(coords[2])
		{}

		inline explicit Vector3(Real* const coords) :
			x(coords[0]), y(coords[1]), z(coords[2])
		{}

		inline explicit Vector3(const Real scalar) :
			x(scalar), y(scalar), z(scalar)
		{}

		inline Real* get()
		{ return &x; }

		inline const Real* get() const
		{ return &x; }

		inline Vector3 operator+ ()
		{ return *this; }

		inline const Vector3& operator+ () const
		{ return *this; }

		inline Vector3 operator- ()
		{ return Vector3(-x, -y, -z); }

		inline Vector3& operator *= (Real scale)
		{
			x *= scale; y *= scale; z *= scale;
			return *this;
		}

		inline Vector3& operator /= (Real scale)
		{
			x /= scale; y /= scale; z /= scale;
			return *this;
		}

		inline Vector3& operator += (const Vector3& v)
		{
			x += v.x; y += v.y; z += v.z;
			return *this;
		}

		inline Vector3& operator -= (const Vector3& v)
		{
			x -= v.x; y -= v.y; z -= v.z;
			return *this;
		}

		inline Real magnitudeSqr() const
		{ return x * x + y * y + z * z; }

		inline Real magnitude() const
		{ return Math::sqrt(magnitudeSqr()); }

		inline Vector3& normalize()
		{
			Real length = magnitude();

			if (length > Real(0.0))
			{
				Real invLength = Real(1.0) / length;
				x *= invLength;
				y *= invLength;
				z *= invLength;
			}

			return *this;
		}

		static const Vector3 ZERO;
		static const Vector3 IDENTITY;

		static inline Vector3 scale(const Vector3& v1, const Vector3& v2)
		{ return Vector3 (v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }

		static inline Real dot(const Vector3& v1, const Vector3& v2)
		{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

		static inline Vector3 cross(const Vector3& v1, const Vector3& v2)
		{
			return Vector3(v1.y * v2.z - v1.z * v2.y,
                           v1.z * v2.x - v1.x * v2.z,
                           v1.x * v2.y - v1.y * v2.x);
		}

		static inline Vector3 middle(const Vector3& v1, const Vector3& v2)
		{
			return Vector3((v1.x + v2.x) * Real(0.5),
						   (v1.y + v2.y) * Real(0.5),
						   (v1.z + v2.z) * Real(0.5));
		}
	public:
		Real x, y, z;
	};

	inline bool operator== (const Vector3& v1, const Vector3& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}

	inline bool operator!= (const Vector3& v1, const Vector3& v2)
	{ 
		return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z; 
	}

	inline Vector3 operator+ (const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	inline Vector3 operator- (const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	inline Vector3 operator* (const Vector3& v, const Real scalar)
	{
		return Vector3(v.x * scalar,
					   v.y * scalar,
					   v.z * scalar);
	}

	inline Vector3 operator* (const Real scalar, const Vector3& v)
	{
		return Vector3(v.x * scalar,
					   v.y * scalar,
					   v.z * scalar);
	}

	inline Vector3 operator/ (const Vector3& v, const Real scalar)
	{
		assert(scalar != Real(0.0));
		Real del = Real(1.0) / scalar;
		return Vector3(v.x * del, v.y * del, v.z * del);
	}
}

#endif /* RAVMATHVECTOR3_H_INCLUDED */
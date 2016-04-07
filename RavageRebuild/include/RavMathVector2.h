#ifndef RAVMATHVECTOR2_H_INCLUDED
#define RAVMATHVECTOR2_H_INCLUDED

#include "RavMathBase.h"

namespace Ravage
{
	class Vector2
	{
	public:
		inline Vector2()
		{}

		inline Vector2(Real fx, Real fy) :
			x(fx), y(fy)
		{}

		inline Real* get()
		{ return &x; }

		inline const Real* get() const
		{ return &x; }

		static const Vector2 ZERO;
		static const Vector2 IDENTITY;

		static inline Vector2 scale(const Vector2& v1, const Vector2& v2)
		{ return Vector2(v1.x * v2.x, v1.y * v2.y); }
	public:
		Real x, y;
	};

	inline Vector2 operator+ (const Vector2& v1, const Vector2& v2)
	{
		return Vector2(v1.x + v2.x, v1.y + v2.y);
	}

	inline Vector2 operator* (Real w, const Vector2& v)
	{
		return Vector2(w * v.x, w * v.y);
	}
}

#endif /* RAVMATHVECTOR2_H_INCLUDED */
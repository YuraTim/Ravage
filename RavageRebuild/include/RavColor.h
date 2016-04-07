#ifndef RAVCOLOR_H_INCLUDED
#define RAVCOLOR_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"

namespace Ravage
{
	class Color
	{
	public:
		inline Color()
		{}

		inline Color(Real fr, Real fg, Real fb, Real fa) :
			r(fr), g(fg), b(fb), a(fa)
		{}

		inline Color(const Vector4& vec) :
			r(vec.x), g(vec.y), b(vec.z), a(vec.w)
		{}

		inline Real* get()
		{ return &r; }

		inline const Real* get() const
		{ return &r; }

		inline operator Vector4() const
		{ return Vector4(r, g, b, a); }

		static const Color WHITE;
		static const Color BLACK;
		static const Color RED;
		static const Color BLUE;
		static const Color GREEN;

	public:
		Real r, g, b, a;
	};
}

#endif /* RAVCOLOR_H_INCLUDED */
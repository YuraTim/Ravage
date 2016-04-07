#ifndef RAVMATHBASE_H_INCLUDED
#define RAVMATHBASE_H_INCLUDED

/* PART OF RAVAGE BASE */

#include <assert.h>
#include <math.h>
#include <string.h>

namespace Ravage
{	
	typedef float Real;

	namespace Math
	{
		const Real PI   = Real(3.14159265358979323846);
		const Real PI_2 = Real(1.57079632679489661923);


#if RAV_MATH_LIB == RAV_MATH_LIB_STD
		//Math.h functions
		inline Real sqrt(Real x)
		{ return ::sqrt(x); }

		inline Real cos(Real x)
		{ return ::cos(x); }

		inline Real sin(Real x)
		{ return ::sin(x); }

		inline Real tan(Real x)
		{ return ::tan(x); }

		inline Real ctan(Real x)
		{ return Real(1.0) / ::tan(x); }

		inline Real abs(Real x)
		{ return ::fabs(x); }
#else
#	error "RAVAGE ERROR: NOT IMPLEMENTED"
#endif
	}
}

#endif // RAVMATHBASE_H_INCLUDED

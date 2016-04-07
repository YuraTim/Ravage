#ifndef RAVMATHMATRIX4_H_INCLUDED
#define RAVMATHMATRIX4_H_INCLUDED

#include "RavMathBase.h"
#include "RavMathVector3.h"
#include "RavMathVector4.h"
#include "RavMathQuaternion.h"

namespace Ravage
{
    class Matrix4
    {
        public:
            inline Matrix4()
            {}

            inline Matrix4(
                Real m00, Real m01, Real m02, Real m03,
                Real m10, Real m11, Real m12, Real m13,
                Real m20, Real m21, Real m22, Real m23,
                Real m30, Real m31, Real m32, Real m33)
            {
                m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
                m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
                m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
                m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
            }
			
			inline Matrix4(Real* matrix)
			{
				memcpy(_m, matrix, sizeof(Real) * 16);
			}

            inline void setScaling(Real scx, Real scy, Real scz)
            { m[0][0] = scx; m[1][1] = scy; m[2][2] = scz; }

            inline void setTranslation(Real ofx, Real ofy, Real ofz)
            {
                m[3][0] = ofx; m[3][1] = ofy; m[3][2] = ofz;
            }

			inline Vector4 getTranslation() const
			{ return Vector4(m[3][0], m[3][1], m[3][2], m[3][3]); }

            inline const Real* get() const
            { return _m; }

            inline Real* get()
            { return _m; }

            inline Real get(int x, int y)
            {
                assert(0 <= x && x < 4);
                assert(0 <= y && y < 4);
                return m[x][y];
            }

			inline Vector4 multiply(const Vector4& v)
			{
				return Vector4(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
							   m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
							   m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
							   m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w);
			}

			inline Vector3 multiplyAffine(const Vector3& v)
			{
				return Vector3(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0],
							   m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1],
							   m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2]);
			}

            static const Matrix4 ZERO;
            static const Matrix4 IDENTITY;

			static inline Matrix4 concatenate(const Matrix4& m1, const Matrix4& m2)
			{
				Matrix4 r;
				r.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
				r.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
				r.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
				r.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

				r.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
				r.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
				r.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
				r.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

				r.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
				r.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
				r.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
				r.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

				r.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
				r.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
				r.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
				r.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

				return r;
			}

			inline bool isAffine() const
			{ return m[0][3] == 0 && m[1][3] == 0 && m[2][3] == 0 && m[3][3] == 1; }

			Real determinantAffine() const;
			Matrix4 inverseAffine() const;

			Real determinant() const;
			Matrix4 inverse() const;

			inline Matrix4 transpose() const
			{
				return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
                               m[0][1], m[1][1], m[2][1], m[3][1],
                               m[0][2], m[1][2], m[2][2], m[3][2],
                               m[0][3], m[1][3], m[2][3], m[3][3]);
			}
        public:
            union
            {
                Real m[4][4];
                Real _m[16];
            };
    };
	
	inline Matrix4& createMatrixScaling(Matrix4& m, Real x, Real y, Real z)
	{
		m = Matrix4::IDENTITY;
		m.setScaling(x, y, z);
		return m;
	}

	inline Matrix4& createMatrixScaling(Matrix4& m, const Vector3& v)
	{
		m.m[0][0] = v.x; m.m[0][1] = 0;   m.m[0][2] = 0;   m.m[0][3] = 0;
		m.m[1][0] = 0;   m.m[1][1] = v.y; m.m[1][2] = 0;   m.m[1][3] = 0;
		m.m[2][0] = 0;   m.m[2][1] = 0;   m.m[2][2] = v.z; m.m[2][3] = 0;
		m.m[3][0] = 0;   m.m[3][1] = 0;   m.m[3][2] = 0;   m.m[3][3] = 1;
		return m;
	}

	inline Matrix4& createMatrixTranslation(Matrix4& m, Real x, Real y, Real z)
	{
		m = Matrix4::IDENTITY;
		m.setTranslation(x, y, z);
		return m;
	}

	inline Matrix4& createMatrixTranslation(Matrix4& m, const Vector3& v)
	{
		m.m[0][0] = 1;   m.m[0][1] = 0;   m.m[0][2] = 0;   m.m[0][3] = 0;
		m.m[1][0] = 0;   m.m[1][1] = 1;   m.m[1][2] = 0;   m.m[1][3] = 0;
		m.m[2][0] = 0;   m.m[2][1] = 0;   m.m[2][2] = 1;   m.m[2][3] = 0;
		m.m[3][0] = v.x; m.m[3][1] = v.y; m.m[3][2] = v.z; m.m[3][3] = 1;
		return m;
	}

	inline Matrix4& createMatrixRotation(Matrix4& m, const Vector3& v, Real angle)
	{
		Real c = Math::cos(angle), nc = Real(1.0) - c, 
			 s = Math::sin(angle);

		Vector3 vnc(nc * v.x, nc * v.y, nc * v.z);
		Vector3 vs(s * v.x, s * v.y, s * v.z);

		m.m[0][0] = v.x * vnc.x + c;    m.m[0][1] = v.x * vnc.y - vs.z; m.m[0][2] = v.x * vnc.z + vs.y; m.m[0][3] = 0;
		m.m[1][0] = v.y * vnc.x + vs.z; m.m[1][1] = v.y * vnc.y + c;    m.m[1][2] = v.y * vnc.z - vs.x; m.m[1][3] = 0;
		m.m[2][0] = v.z * vnc.x - vs.y; m.m[2][1] = v.z * vnc.y + vs.x; m.m[2][2] = v.z * vnc.z + c;    m.m[2][3] = 0;
		m.m[3][0] = 0;                  m.m[3][1] = 0;                  m.m[3][2] = 0;                  m.m[3][3] = 1;
		
		return m;
	}

	inline Matrix4& createMatrixRotation(Matrix4& m, const Quaternion& q)
	{
		Real xx = 2 * q.v.x * q.v.x, 
			 xy = 2 * q.v.x * q.v.y,
			 xz = 2 * q.v.x * q.v.z,
			 xw = 2 * q.v.x * q.w;

		Real yy = 2 * q.v.y * q.v.y,
			 yz = 2 * q.v.y * q.v.z,
			 yw = 2 * q.v.y * q.w;
		
		Real zz = 2 * q.v.z * q.v.z,
			 zw = 2 * q.v.z * q.w;

		m.m[0][0] = 1 - yy - zz; m.m[0][1] = xy + zw;     m.m[0][2] = xz - yw;     m.m[0][3] = 0;
		m.m[1][0] = xy - zw;     m.m[1][1] = 1 - xx - zz; m.m[1][2] = yz + xw;     m.m[1][3] = 0;
		m.m[2][0] = xz + yw;     m.m[2][1] = yz - xw;     m.m[2][2] = 1 - xx - yy; m.m[2][3] = 0;
		m.m[3][0] = 0;           m.m[3][1] = 0;           m.m[3][2] = 0;           m.m[3][3] = 1;

		return m;
	}

	inline Matrix4& createMatrixOrthoLH(Matrix4& m, Real l, Real r, Real b, Real t, Real zn, Real zf)
    {
        m.m[0][0] = 2 / (r - l);       m.m[0][1] = 0;                 m.m[0][2] = 0;              m.m[0][3] = 0;
        m.m[1][0] = 0;                 m.m[1][1] = 2 / (t - b);       m.m[1][2] = 0;              m.m[1][3] = 0;
        m.m[2][0] = 0;                 m.m[2][1] = 0;                 m.m[2][2] = 1 / (zf - zn);  m.m[2][3] = 0;
        m.m[3][0] = (l + r) / (l - r); m.m[3][1] = (t + b) / (b - t); m.m[3][2] = zn / (zn - zf); m.m[3][3] = 1;
		return m;
    }

	inline Matrix4& createMatrixOrthoRH(Matrix4& m, Real l, Real r, Real b, Real t, Real zn, Real zf)
    {
        m.m[0][0] = 2 / (r - l);       m.m[0][1] = 0;                 m.m[0][2] = 0;              m.m[0][3] = 0;
        m.m[1][0] = 0;                 m.m[1][1] = 2 / (t - b);       m.m[1][2] = 0;              m.m[1][3] = 0;
        m.m[2][0] = 0;                 m.m[2][1] = 0;                 m.m[2][2] = 1 / (zn - zf);  m.m[2][3] = 0;
        m.m[3][0] = (l + r) / (l - r); m.m[3][1] = (t + b) / (b - t); m.m[3][2] = zn / (zn - zf); m.m[3][3] = 1;
		return m;
    }

	inline Matrix4& createMatrixOrtho(Matrix4& m, Real l, Real r, Real b, Real t, Real zn, Real zf)
	{
		//TODO: RIGHT COORDINATES ORIENTATION
		return createMatrixOrthoLH(m, l, r, b, t, zn, zf);
	}

	inline Matrix4& createMatrixLookAtLH(Matrix4& m, const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Vector3 zaxis = (at - eye).normalize();
		Vector3 xaxis = Vector3::cross(up, zaxis).normalize();
		Vector3 yaxis = Vector3::cross(zaxis, xaxis);

		m.m[0][0] = xaxis.x;                   m.m[0][1] = yaxis.x;                   m.m[0][2] = zaxis.x;                   m.m[0][3] = 0;
		m.m[1][0] = xaxis.y;                   m.m[1][1] = yaxis.y;                   m.m[1][2] = zaxis.y;                   m.m[1][3] = 0;
		m.m[2][0] = xaxis.z;                   m.m[2][1] = yaxis.z;                   m.m[2][2] = zaxis.z;                   m.m[2][3] = 0;
		m.m[3][0] = -Vector3::dot(xaxis, eye); m.m[3][1] = -Vector3::dot(yaxis, eye); m.m[3][2] = -Vector3::dot(zaxis, eye); m.m[3][3] = 1;
		
		return m;
	}

	inline Matrix4& createMatrixLookAtRH(Matrix4& m, const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Vector3 zaxis = (eye - at).normalize();
		Vector3 xaxis = Vector3::cross(up, zaxis).normalize();
		Vector3 yaxis = Vector3::cross(zaxis, xaxis);

		m.m[0][0] = xaxis.x;                   m.m[0][1] = yaxis.x;                   m.m[0][2] = zaxis.x;                   m.m[0][3] = 0;
		m.m[1][0] = xaxis.y;                   m.m[1][1] = yaxis.y;                   m.m[1][2] = zaxis.y;                   m.m[1][3] = 0;
		m.m[2][0] = xaxis.z;                   m.m[2][1] = yaxis.z;                   m.m[2][2] = zaxis.z;                   m.m[2][3] = 0;
		m.m[3][0] = -Vector3::dot(xaxis, eye); m.m[3][1] = -Vector3::dot(yaxis, eye); m.m[3][2] = -Vector3::dot(zaxis, eye); m.m[3][3] = 1;
		
		return m;
	}

	inline Matrix4& createMatrixLookAt(Matrix4& m, const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		//TODO: RIGHT COORDINATES ORIENTATION
		return createMatrixLookAtLH(m, eye, at, up);
	}

	inline Matrix4& createMatrixPerspectiveFovLH(Matrix4& m, Real fovy, Real aspect, Real zn, Real zf)
	{
		Real yScale = Math::ctan(fovy / 2);
		Real xScale = yScale / aspect;

		m.m[0][0] = xScale; m.m[0][1] = 0;      m.m[0][2] = 0;                   m.m[0][3] = 0;
		m.m[1][0] = 0;      m.m[1][1] = yScale; m.m[1][2] = 0;                   m.m[1][3] = 0;
		m.m[2][0] = 0;      m.m[2][1] = 0;      m.m[2][2] = zf / (zf - zn);      m.m[2][3] = 1;
		m.m[3][0] = 0;      m.m[3][1] = 0;      m.m[3][2] = zn * zf / (zn - zf); m.m[3][3] = 0;

		return m;
	}

	/*inline Matrix4& createMatrixPerspectiveFovRH(Matrix4& m, Real fovy, Real aspect, Real zn, Real zf)
	{
		Real yScale = Math::ctan(fovy / 2);
		Real xScale = yScale / aspect;

		m.m[0][0] = xScale; m.m[0][1] = 0;      m.m[0][2] = 0;                   m.m[0][3] = 0;
		m.m[1][0] = 0;      m.m[1][1] = yScale; m.m[1][2] = 0;                   m.m[1][3] = 0;
		m.m[2][0] = 0;      m.m[2][1] = 0;      m.m[2][2] = zf / (zn - zf);      m.m[2][3] = -1;
		m.m[3][0] = 0;      m.m[3][1] = 0;      m.m[3][2] = zn * zf / (zn - zf); m.m[3][3] = 0;

		return m;
	}*/

	inline Matrix4& createMatrixPerspectiveFovRH(Matrix4& m, Real fovy, Real aspect, Real zn, Real zf)
	{
		Real range  = Math::tan(fovy / Real(2)) * zn;	
		Real l = -range * aspect;
		Real r =  range * aspect;
		Real b = -range;
		Real t =  range;
	
		m.m[0][0] = 2 * zn / (r - l); m.m[0][1] = 0;                m.m[0][2] = 0;                       m.m[0][3] = 0;
		m.m[1][0] = 0;                m.m[1][1] = 2 * zn / (t - b); m.m[1][2] = 0;                       m.m[1][3] = 0;
		m.m[2][0] = 0;                m.m[2][1] = 0;                m.m[2][2] = (zf + zn) / (zn - zf);   m.m[2][3] = -1;
		m.m[3][0] = 0;                m.m[3][1] = 0;                m.m[3][2] = 2 * zn * zf / (zn - zf); m.m[3][3] = 0;

		return m;
	}

	inline Matrix4& createMatrixPerspectiveFov(Matrix4& m, Real fovy, Real aspect, Real zn, Real zf)
	{
		//TODO: RIGHT COORDINATES ORIENTATION
		return createMatrixPerspectiveFovLH(m, fovy, aspect, zn, zf);
	}

	inline Matrix4& createMatrixPerspectiveLH(Matrix4& m, Real w, Real h, Real zn, Real zf)
	{
		m.m[0][0] = 2 * zn / w; m.m[0][1] = 0;          m.m[0][2] = 0;                   m.m[0][3] = 0;
		m.m[1][0] = 0;          m.m[1][1] = 2 * zn / h; m.m[1][2] = 0;                   m.m[1][3] = 0;
		m.m[2][0] = 0;          m.m[2][1] = 0;          m.m[2][2] = zf / (zf - zn);      m.m[2][3] = 1;
		m.m[3][0] = 0;          m.m[3][1] = 0;          m.m[3][2] = zn * zf / (zn - zf); m.m[3][3] = 0;
		return m;
	}

	inline Matrix4& createMatrixPerspectiveRH(Matrix4& m, Real w, Real h, Real zn, Real zf)
	{
		m.m[0][0] = 2 * zn / w; m.m[0][1] = 0;          m.m[0][2] = 0;                   m.m[0][3] = 0;
		m.m[1][0] = 0;          m.m[1][1] = 2 * zn / h; m.m[1][2] = 0;                   m.m[1][3] = 0;
		m.m[2][0] = 0;          m.m[2][1] = 0;          m.m[2][2] = zf / (zn - zf);      m.m[2][3] = -1;
		m.m[3][0] = 0;          m.m[3][1] = 0;          m.m[3][2] = zn * zf / (zn - zf); m.m[3][3] = 0;
		return m;
	}

	inline Matrix4& createMatrixPerspective(Matrix4& m, Real w, Real h, Real zn, Real zf)
	{
		//TODO: RIGHT COORDINATES ORIENTATION
		return createMatrixPerspectiveLH(m, w, h, zn, zf);
	}
}

#endif // RAVMATHMATRIX4_H_INCLUDED

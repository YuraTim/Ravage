#ifndef RAVMATERIAL_H_INCLUDED
#define RAVMATERIAL_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"
#include "RavShader.h"
#include "RavColor.h"
#include "RavListener.h"

namespace Ravage
{
	class Material
	{
	public:
		enum EventList
		{
			EVENT_ONSHADERCHANGED,
			EVENT_SIZE
		};

		Material();

		bool setShader(Shader* shader);
		inline Shader* getShader()
		{ return mShader; }

		inline Listener* getListener()
		{ return &mListener; }

	private:
		bool updateShaderDecl();

	private:
		enum PropertyType
		{
			PT_REAL = 0,
			PT_VECTOR,
			PT_COLOR,
			PT_MATRIX,

		};

		struct Property
		{
			String       name;
			unsigned     uniformId;
			PropertyType type;
			unsigned     valueOffset;
		};
		Listener mListener;		

		Shader* mShader;

		//TODO: Remove map
		std::map<String, Property> mPropertyMap;
		//TODO: Remove vector
		std::vector<Real>    mRealValue;
		std::vector<Vector4> mVectorValue;
		std::vector<Color>   mColorValue;
		std::vector<Matrix4> mMatrixValue;
	};
}

#endif /* RAVMATERIAL_H_INCLUDED */
#include "RavMaterial.h"

namespace Ravage
{
	Material::Material() :
		mListener(EVENT_SIZE),
		mShader(0)
	{}

	bool Material::setShader(Shader* shader)
	{
		mShader = shader;
		if (!updateShaderDecl())
		{
			mShader = 0;
			return false;
		}
		mListener.raiseEvent(EVENT_ONSHADERCHANGED);
		return true;
	}

	bool Material::updateShaderDecl()
	{
		if (!mShader)
		{
			//TODO: Log error.
			return false;
		}

		mRealValue.clear();
		mVectorValue.clear();
		mColorValue.clear();
		mMatrixValue.clear();

		int count = mShader->getDeclCount();
		for (int ind  = 0; ind < count; ind++)
		{
			Property prop;
			const Shader::Declaration* decl = mShader->getDeclaration(ind);

			prop.name = decl->name;
			if (decl->type == RAV_TXT("Real"))
			{
				prop.type        = PT_REAL;
				prop.valueOffset = mRealValue.size();
				mRealValue.push_back(Real(0));
			}
			else if (decl->type == RAV_TXT("Vector"))
			{
				prop.type        = PT_VECTOR;
				prop.valueOffset = mVectorValue.size();
				mVectorValue.push_back(Vector4(Real(0), Real(0), Real(0), Real(0)));
			}
			else if (decl->type == RAV_TXT("Color"))
			{
				prop.type        = PT_COLOR;
				prop.valueOffset = mColorValue.size();
				mColorValue.push_back(Color(Real(0), Real(0), Real(0), Real(1)));
			}
			else if (decl->type == RAV_TXT("Matrix"))
			{
				prop.type        = PT_MATRIX;
				prop.valueOffset = mMatrixValue.size();
				mMatrixValue.push_back(Matrix4::ZERO);
			}
			else
			{
				//TODO: Error log.
				mRealValue.clear();
				mVectorValue.clear();
				mColorValue.clear();
				mMatrixValue.clear();
				return false;
			}
		}
		return true;
	}
}
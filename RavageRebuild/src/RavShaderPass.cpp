#include "RavShaderPass.h"

namespace Ravage
{
	ShaderPass::ShaderPass() :
		mSourceType(0),
		mUseVertexShader(false),
		mUseGeometryShader(false),
		mUsePixelShader(false)
	{}

	ShaderPass::~ShaderPass()
	{}
}
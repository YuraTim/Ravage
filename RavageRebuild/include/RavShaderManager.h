#ifndef RAVRENDERMANAGER_H_INCLUDED
#define RAVRENDERMANAGER_H_INCLUDED

#include "RavBase.h"
#include "RavShader.h"
#include "RavRenderable.h"

namespace Ravage
{
	class RenderManager : public Singleton<RenderManager>
	{
	public:
		Shader* createShader();

		template<class Type>
		Renderable* createRenderable();

		void release(Renderable* renderer);
		void release(Shader* shader);


	private:
		struct ShaderPrior
		{
			Shader* shader;
			List<Renderable*> objects;
		};

		List<ShaderPrior> mShaderObjects;
	private:
		List<ShaderPrior>* getShader(Shader* shader);
	};
}

#endif /* RAVRENDERMANAGER_H_INCLUDED */
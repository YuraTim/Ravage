#ifndef RAVSHADER_H_INCLUDED
#define RAVSHADER_H_INCLUDED

#include "RavBase.h"
#include "RavMath.h"
#include "RavResourceAsset.h"
#include "RavGraphicEnum.h"
#include "RavShaderPass.h"

//!!! TODO: Remove Cg from here cuz OpenGL ES doesn't support it.
//!!! TODO: SubShader support!

namespace Ravage
{
	class RenderCore;

	class Shader : public ResourceAsset
	{
	public:
		struct Declaration
		{
			String name;
			String displayName;
			String type;
			String defaultValue;
		};

		Shader();
		~Shader();

		virtual bool load(Byte* bytes, int size);
		virtual bool load(File& file);
		virtual bool load(const String& filename);

		bool compile();

		bool beginPass(int pass);
		bool endPass();

		inline int getPassCount() const
		{ return mPasses.size(); }
		
		inline ShaderPass* getPass(int pass)
		{ return mPasses.at(pass); }

		const String& getShaderName() const
		{ return mName; }

		inline int getDeclCount() const
		{ return mDeclarations.size(); }

		inline const Declaration* getDeclaration(int ind) const
		{ return &mDeclarations.at(ind); }

	private:
		bool parseShader(Node* node);
		bool parseSubShader(Node* node);
		bool parsePass(Node* node, 
					   const std::vector<String>& sources);
		bool parseDeclaration(Node* node);
	private:

		RenderCore* mRenderCore;
		String mName;

		//TODO: Remove vector.
		std::vector<ShaderPass*> mPasses;
		std::vector<Declaration> mDeclarations;
	};
}

#endif /* RAVSHADER_H_INCLUDED */
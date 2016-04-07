#include "RavShader.h"
#include "RavRenderCore.h"

namespace Ravage
{
	Shader::Shader() :
		mRenderCore(RenderCore::instance()),
		mName(RAV_TXT("INVALID"))
	{}

	Shader::~Shader()
	{
		Renderer* renderer = mRenderCore->getRenderer();
		RavAssert(renderer);

		for (std::vector<ShaderPass*>::iterator iter = mPasses.begin(); iter != mPasses.end(); ++iter)
			renderer->release(*iter);
	}

	bool Shader::load(Byte* mem, int size)
	{
		return ResourceAsset::load(mem, size);
	}

	bool Shader::load(File& file)
	{
		if (!ResourceAsset::load(file))
			return false;

		Node* main = getMainNode();

		for (NodeId id = main->structs.begin(); id != main->structs.end(); ++id)
			if ((*id)->type == RAV_TXT("Shader"))
				return parseShader(*id);

		return false;
	}

	bool Shader::parseShader(Node* node)
	{
		mName = node->name;
		for (NodeId id = node->structs.begin(); id != node->structs.end(); ++id)
		{
			if ((*id)->type == RAV_TXT("Declare"))
			{
				if (!parseDeclaration(*id))
					return false;
			}
			else if ((*id)->type == RAV_TXT("SubShader"))
			{
				if (!parseSubShader(*id))
					return false;
			}
		}
		return true;
	}

	bool Shader::parseSubShader(Node* node)
	{
		std::vector<String> sources;
		for (NodeId id = node->structs.begin(); id != node->structs.end(); ++id)
		{
			if ((*id)->type == RAV_TXT("SHADER"))
				sources.push_back((*id)->name);
			else if ((*id)->type == RAV_TXT("Include"))
			{
				File file;
				if (!file.open((*id)->name, RAV_FMODE_READ | RAV_FMODE_TEXT))
				{
					//TODO: Error log.
					return false;
				}

				String includeSource;
				if (!file.readLine(includeSource, StringUtils::BLANK))
				{
					//TODO: Error log.
					return false;
				}
				sources.push_back(includeSource);
			}
			else if ((*id)->type == RAV_TXT("Pass"))
			{
				if (!parsePass(*id, sources))
					return false;
			}
		}
		return true;
	}

	//TODO: Shader type.
	bool Shader::parsePass(Shader::Node* node, const std::vector<String>& sources)
	{
		Renderer* renderer = mRenderCore->getRenderer();
		RavAssert(renderer);

		ShaderPass* pass = renderer->createShaderPass();
		for (std::vector<String>::const_iterator iter = sources.begin(); iter != sources.end(); ++iter)
		{
			if (!pass->addSource(*iter))
			{
				renderer->release(pass);
				return false;
			}
		}

		for (NodeId id = node->structs.begin(); id != node->structs.end(); ++id)
		{
			if ((*id)->type == RAV_TXT("SHADER"))
			{
				if (!pass->addSource((*id)->name))
				{
					renderer->release(pass);
					return false;
				}
			}
			else if ((*id)->type == RAV_TXT("VertexShader"))
			{
				if ((*id)->name == RAV_TXT("On"))
					pass->setVertexShaderOn(true);
				else
					pass->setVertexShaderOn(false);
			}
			else if ((*id)->type == RAV_TXT("GeometryShader"))
			{
				if ((*id)->name == RAV_TXT("On"))
					pass->setGeometryShaderOn(true);
				else
					pass->setGeometryShaderOn(false);
			}
			else if ((*id)->type == RAV_TXT("PixelShader"))
			{
				if ((*id)->name == RAV_TXT("On"))
					pass->setPixelShaderOn(true);
				else
					pass->setPixelShaderOn(false);
			}
		}

		mPasses.push_back(pass);
		return true;
	}

	bool Shader::parseDeclaration(Shader::Node* node)
	{
		Declaration result;

		result.name = node->name;

		for (NodeId id = node->structs.begin(); id != node->structs.end(); ++id)
		{
			if ((*id)->type == RAV_TXT("Type") || (*id)->type == RAV_TXT("type"))
				result.type = (*id)->name;
			else if ((*id)->type == RAV_TXT("Name") || (*id)->type == RAV_TXT("name"))
				result.displayName = (*id)->name;
			else if ((*id)->type == RAV_TXT("Default") || (*id)->type == RAV_TXT("default"))
				result.defaultValue = (*id)->name;
		}
		return true;
	}

	bool Shader::load(const String& filename)
	{
		return ResourceAsset::load(filename);
	}

	bool Shader::compile()
	{
		for (std::vector<ShaderPass*>::iterator iter = mPasses.begin(); iter != mPasses.end(); ++iter)
		{
			if (!(*iter)->compile())
			{
				//TODO: Log error.
				//TODO: Release resources.
				return false;
			}
		}
		return true;
	}

	bool Shader::beginPass(int passid)
	{
		ShaderPass* pass     = mPasses.at(passid);
		Renderer*   renderer = mRenderCore->getRenderer();

		RavAssert(renderer);

		return renderer->loadShaderPass(pass);
	}

	bool Shader::endPass()
	{
		Renderer*   renderer = mRenderCore->getRenderer();

		RavAssert(renderer);
		return renderer->unloadShaderPass();
	}
}
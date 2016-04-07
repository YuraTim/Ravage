#ifndef RAVRESOURCEASSET_H_INCLUDED
#define RAVRESOURCEASSET_H_INCLUDED

#include "RavBase.h"
#include "RavAsset.h"

namespace Ravage
{
	struct ResourceAssetStruct
	{
		ResourceAssetStruct(const String& t = RAV_TXT(""), 
							const String& n = RAV_TXT(""));
		~ResourceAssetStruct();

		String type;
		String name;

		//TODO: remove vector.
		std::vector<ResourceAssetStruct*> structs;
	};

	class ResourceAsset : public Asset
	{
	public:
		typedef ResourceAssetStruct Node;
		typedef std::vector<Node*>::iterator NodeId;
		
		ResourceAsset();

		virtual bool load(Byte* byte, int size);
		virtual bool load(File& file);
		virtual bool load(const String& filename);

		inline Node* getMainNode()
		{ return &mMainStruct; }

	private:
		bool parseStruct(ResourceAssetStruct* current, String& code); 
		bool parseParameter(ResourceAssetStruct* current, const String& name, String& code);
	private:
		//TODO: implement:
		ResourceAsset& operator= (ResourceAsset& asset);
		ResourceAsset(const ResourceAsset&);

		ResourceAssetStruct mMainStruct;
	};
}

#endif /* RAVRESOURCEASSET_H_INCLUDED */
#ifndef MESHLOADEROBJ_H_INCLUDED
#define MESHLOADEROBJ_H_INCLUDED

#include "RavBase.h"
#include "RavVertexData.h"
#include "RavVertexDeclaration.h"
#include "RavRenderCore.h"
#include "RavStringUtils.h"

class MeshLoaderObj
{
public:
	MeshLoaderObj();
	~MeshLoaderObj();

	Ravage::VertexData* getVertexData()
	{ return mVertexData; }

	Ravage::DrawOperation* getDrawOperation()
	{ return &mDrawOperation; }

	bool load(const Ravage::String& filename);

private:
	bool addValues(const Ravage::String& cmd, std::vector<Ravage::Real>& values);
	bool addFace(int* pInd, int* nInd, int* tInd);
	bool createVertexData();

	Ravage::RenderCore* mRenderCore;
	Ravage::Renderer* mRenderer;

	Ravage::DrawOperation mDrawOperation;

	Ravage::VertexDeclaration* mDeclaration;
	Ravage::VertexBuffer* mVertexBuffer;
	Ravage::VertexData* mVertexData;

	bool mHasPositions;
	bool mHasNormals;
	bool mHasTexCoords;

	std::vector<Ravage::Real> mPositions;
	std::vector<Ravage::Real> mNormals;
	std::vector<Ravage::Real> mTexCoords;

	std::vector<Ravage::Real> mData;
};

#endif /* MESHLOADEROBJ_H_INCLUDED */
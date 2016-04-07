#include "MeshLoaderObj.h"

MeshLoaderObj::MeshLoaderObj() :
	mRenderCore(Ravage::RenderCore::instance()),
	mRenderer(0),
	mDeclaration(0),
	mVertexBuffer(0),
	mVertexData(0),
	mHasPositions(0),
	mHasNormals(0),
	mHasTexCoords(0)
{
	mDrawOperation.operationType = Ravage::DrawOperation::TYPE_TRIANGLE_LIST;
	mDrawOperation.primitiveCount = 0;
	mDrawOperation.startIndex = 0;
	mDrawOperation.startVertex = 0;
}

MeshLoaderObj::~MeshLoaderObj()
{
	if (mDeclaration)
		delete mDeclaration;

	if (mVertexBuffer)
		mRenderer->release(mVertexBuffer);

	if (mVertexData)
		mRenderer->release(mVertexData);

	mRenderCore->freeInst();
}

bool MeshLoaderObj::load(const Ravage::String& filename)
{
	mRenderer = mRenderCore->getRenderer();

	Ravage::File file;
	if (!file.open(filename, Ravage::RAV_FMODE_READ | Ravage::RAV_FMODE_TEXT))
		return false;

	mDrawOperation.primitiveCount = 0;

	Ravage::String line;
	while (!file.isEnd())
	{
		file.readLine(line, RAV_TXT("\n"));

		Ravage::String::size_type trim = line.find_first_of(RAV_TXT("#"));
		line = line.substr(0, trim);

		Ravage::StringUtils::trim(line);

		std::basic_istringstream<Ravage::Symbol> iss(line);

		Ravage::String cmd;
		iss >> cmd;

		if (cmd == RAV_TXT("v") || cmd == RAV_TXT("vt") || cmd == RAV_TXT("vn"))
		{
			std::vector<Ravage::Real> values;
			Ravage::Real val = 0.0f;

			while (!iss.eof())
			{
				iss >> val;
				values.push_back(val);
			}

			if (!addValues(cmd, values))
				return false;
		}
		else if (cmd == RAV_TXT("f"))
		{
			bool has[3] = {0};

			int pInd[3] = {0};
			int nInd[3] = {0};
			int tInd[3] = {0};
			
			for (int i = 0; i < 3; i++)
			{
				Ravage::String ind;
				iss >> ind;

				Ravage::String::size_type fslash = ind.find_first_of(RAV_TXT('/'));
				Ravage::String::size_type sslash = ind.find_last_of(RAV_TXT('/'));

				if (fslash == Ravage::String::npos)
				{
					pInd[i] = Ravage::StringUtils::toInt(ind);
					has[0] = true;
				}
				else if (fslash == sslash)
				{
					pInd[i] = Ravage::StringUtils::toInt(ind.substr(0, fslash));
					tInd[i] = Ravage::StringUtils::toInt(ind.substr(sslash + 1));
					has[0] = has[1] = true;
				}
				else
				{
					pInd[i] = Ravage::StringUtils::toInt(ind.substr(0, fslash));
					tInd[i] = Ravage::StringUtils::toInt(ind.substr(fslash + 1, sslash - 1));
					nInd[i] = Ravage::StringUtils::toInt(ind.substr(sslash + 1));
					has[0] = has[2] = true;
					has[1] = sslash - fslash - 1 > 0;
				}

				mHasPositions |= has[0]; mHasTexCoords |= has[1]; mHasNormals |= has[2];
			}


			int* pRes = has[0] ? pInd : 0;
			int* tRes = has[1] ? tInd : 0;
			int* nRes = has[2] ? nInd : 0;
			if (!addFace(pRes, tRes, nRes))
				return false;
		}
	}

	return createVertexData();
}


bool MeshLoaderObj::addValues(const Ravage::String& cmd, std::vector<Ravage::Real>& values)
{
	if (cmd == RAV_TXT("v"))
	{
		while (values.size() < 3)
			values.push_back(0.0f);

		if (values.size() == 3)
			values.push_back(1.0f);

		if (values.size() > 4)
			return false;

		mPositions.insert(mPositions.end(), values.begin(), values.end());
	}
	else if (cmd == RAV_TXT("vt"))
	{
		if (values.size() > 3)
			return false;

		if (values.size() == 3)
		{
			values[0] /= values[2];
			values[1] /= values[2];
			values.pop_back();
		}

		mTexCoords.insert(mTexCoords.end(), values.begin(), values.end());
	}
	else if (cmd == RAV_TXT("vn"))
	{
		if (values.size() > 4)
			return false;

		while(values.size() < 3)
			values.push_back(0.0f);
		if (values.size() == 4)
		{
			values[0] /= values[3];
			values[1] /= values[3];
			values[2] /= values[3];
			values.pop_back();
		}

		mNormals.insert(mNormals.end(), values.begin(), values.end());
	}
	return true;
}

bool MeshLoaderObj::addFace(int* pInd, int* tInd, int* nInd)
{
	for (int i = 0; i < 3; i++)
	{
		if (pInd)
		{
			if (mPositions.size() /  4 < (unsigned) pInd[i] - 1)
				return false;

			mData.insert(mData.end(), mPositions.begin() + 4 * (pInd[i] - 1), mPositions.begin() + 4 * pInd[i]);
		}
		else if (mHasPositions)
			return false;

		if (tInd)
		{
			if (mTexCoords.size() / 2 < (unsigned) tInd[i] - 1)
				return false;

			mData.insert(mData.end(), mTexCoords.begin() + 2 * (tInd[i] - 1), mTexCoords.begin() + 2 * tInd[i]);
		}
		else if (mHasTexCoords)
			return false;

		if (nInd)
		{
			if (mNormals.size() / 3 < (unsigned) nInd[i] - 1)
				return false;

			mData.insert(mData.end(), mNormals.begin() + 3 * (nInd[i] - 1), mNormals.begin() + 3 * nInd[i]);
		}
		else if (mHasNormals)
			return false;
	}
	mDrawOperation.primitiveCount++;
	return true;
}

bool MeshLoaderObj::createVertexData()
{
	mDeclaration = new Ravage::VertexDeclaration();

	if (mHasPositions)
		mDeclaration->addElement(0, Ravage::VertexDeclaration::TYPE_REAL4, Ravage::VertexDeclaration::USAGE_POSITION);
	if (mHasTexCoords)
		mDeclaration->addElement(0, Ravage::VertexDeclaration::TYPE_REAL2, Ravage::VertexDeclaration::USAGE_TEXCOORD);
	if (mHasNormals)
		mDeclaration->addElement(0, Ravage::VertexDeclaration::TYPE_REAL3, Ravage::VertexDeclaration::USAGE_NORMAL);

	mVertexBuffer = mRenderer->createVertexBuffer(mData.size() * sizeof(Ravage::Real), Ravage::GR_TYPE_STATIC);
	if (!mVertexBuffer)
		return false;
	
	mVertexBuffer->setBuffer((Ravage::Byte*)mData.data(), mData.size() * sizeof(Ravage::Real));
	mVertexData = mRenderer->createVertexData(mDeclaration);
	if (!mVertexData)
		return false;

	mVertexData->addStream(mVertexBuffer);
	if (!mVertexData->generateStreamInfo())
		return false;
	return true;
}

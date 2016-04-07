#include "OpenGL/RavVertexDataOpenGL.h"

#include "OpenGL/RavVertexBufferOpenGL.h"

namespace Ravage
{
	VertexDataOpenGL::VertexDataOpenGL(VertexDeclaration* decl) :
		VertexData(decl),
		mVertexArray(0)
	{}

	VertexDataOpenGL::~VertexDataOpenGL()
	{
		if (mVertexArray)
		{
			glDeleteVertexArrays(1, &mVertexArray);
			mVertexArray = 0;
		}
	}
	
	//Attribute map:
	//ATTR0  - POSITION0
	//ATTR1  - POSITION1
	//ATTR2  - NORMAL
	//ATTR3  - COLOR0
	//ATTR4  - COLOR1
	//ATTR5  - FOGCOORD
	//ATTR6  - 
	//ATTR7  - 
	//ATTR8  - TEXCOORD0
	//ATTR9  - TEXCOORD1
	//ATTR10 - TEXCOORD2
	//ATTR11 - TEXCOORD3
	//ATTR12 - TEXCOORD4
	//ATTR13 - TEXCOORD5
	//ATTR14 - TEXCOORD6
	//ATTR15 - TEXCOORD7
	bool VertexDataOpenGL::generateStreamInfo()
	{
		if (!mVertexArray)
			glGenVertexArrays(1, &mVertexArray);

		glBindVertexArray(mVertexArray);

		VertexDeclaration* decl = getDeclaration();
		RavAssert(decl);

		ushort size = getStreamCount();
		for (ushort stream = 0; stream < size; ++stream)
		{
			//TODO: dynamic_cast
			VertexBufferOpenGL* buffer = (VertexBufferOpenGL*)getStream(stream);
			RavAssert(buffer);

			glBindBuffer(GL_ARRAY_BUFFER, buffer->getBufferID());

			//TODO: Check reenabling already enabled states.
			unsigned offset = 0;
			unsigned stride = decl->getStreamVertexSize(stream);
			unsigned streamSize = decl->getElementsCount(stream);
			for (unsigned elementID = 0; elementID < streamSize; ++elementID)
			{
				VertexDeclaration::Element* element = decl->getElement(stream, elementID);

				GLint  size = 0;
				GLenum type = 0;

				switch (element->type)
				{
				case VertexDeclaration::TYPE_BYTE3:
					size = 3;
					type = GL_BYTE;
					break;
				case VertexDeclaration::TYPE_BYTE4:
					size = 4;
					type = GL_BYTE;
					break;
				case VertexDeclaration::TYPE_REAL1:
					size = 1;
					type = GL_FLOAT;
					break;
				case VertexDeclaration::TYPE_REAL2:
					size = 2;
					type = GL_FLOAT;
					break;
				case VertexDeclaration::TYPE_REAL3:
					size = 3;
					type = GL_FLOAT;
					break;
				case VertexDeclaration::TYPE_REAL4:
					size = 4;
					type = GL_FLOAT;
					break;
				}

				switch (element->usage)
				{
				case VertexDeclaration::USAGE_POSITION:
					RavAssert(element->usageIndex <= 1);
					glEnableVertexAttribArray(element->usageIndex);
					glVertexAttribPointer(element->usageIndex, size, type, GL_FALSE, stride, (char*)0 + offset);
					break;
				case VertexDeclaration::USAGE_NORMAL:
					RavAssert(size == 3);
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, size, type, GL_FALSE, stride, (char*)0 + offset);
					break;
				case VertexDeclaration::USAGE_COLOR:
					RavAssert(element->usageIndex <= 1);
					glEnableVertexAttribArray(3 + element->usageIndex);
					glVertexAttribPointer(3 + element->usageIndex, size, type, GL_FALSE, stride, (char*)0 + offset);
					break;
				case VertexDeclaration::USAGE_TEXCOORD:
					RavAssert(element->usageIndex <= 8);
					glEnableVertexAttribArray(8 + element->usageIndex);
					glVertexAttribPointer(8 + element->usageIndex, size, type, GL_FALSE, stride, (char*)0 + offset);
					break;
				}

				offset += decl->getTypeSize(element->type);
			}
		}
		glBindVertexArray(0);
		return true;
	}
}
#ifndef RAVVERTEXDATAOPENGL_H_INCLUDED
#define RAVVERTEXDATAOPENGL_H_INCLUDED

#include "RavBase.h"
#include "RavVertexData.h"

#include "OpenGL/RavLibrariesOpenGL.h"

namespace Ravage
{
	class VertexDataOpenGL : public VertexData
	{
	public:
		VertexDataOpenGL(VertexDeclaration* decl);
		~VertexDataOpenGL();

		virtual bool generateStreamInfo();

		inline GLuint getVertexArray()
		{
			return mVertexArray;
		}
	private:
		GLuint mVertexArray;
	};
}

#endif /* RAVVERTEXDATAOPENGL_H_INCLUDED */
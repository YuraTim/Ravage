#ifndef RAVVERTEXDECLARATION_H_INCLUDED
#define RAVVERTEXDECLARATION_H_INCLUDED

#include "RavBase.h"

namespace Ravage
{
	class VertexDeclaration
	{
	public:
		enum ElementType
		{
			TYPE_REAL1,
			TYPE_REAL2,
			TYPE_REAL3,
			TYPE_REAL4,
			TYPE_BYTE3,
			TYPE_BYTE4
		};

		enum ElementUsage
		{
			USAGE_POSITION,
			USAGE_NORMAL,
			USAGE_TEXCOORD,
			USAGE_COLOR
		};

		struct Element
		{
			ushort       stream;
			ElementType  type;
			ElementUsage usage;
			char         usageIndex;
		};

		inline void addElement(ushort       stream     = 0,
							   ElementType  type       = TYPE_REAL3,
							   ElementUsage usage      = USAGE_POSITION,
							   char         usageIndex = 0)
		{
			Element el = {stream, type, usage, usageIndex};
			addElement(el);
		}

		void addElement(const Element& element);

		inline void addElements(Element* element)
		{
			while (element)
				addElement(*element++);
		}

		inline void clearElements()
		{ mElements.clear(); }

		inline void loadDefaultDiffuse()
		{
			clearElements();
			addElement(0, TYPE_REAL3, USAGE_POSITION, 0);
			addElement(0, TYPE_REAL3, USAGE_NORMAL, 0);
			addElement(0, TYPE_REAL2, USAGE_TEXCOORD, 0);
			addElement(0, TYPE_BYTE4, USAGE_COLOR, 0);
		}

		unsigned getStreamVertexSize(ushort streamIdx) const;

		inline unsigned getElementsCount(ushort streamIdx) const
		{ return mElements.at(streamIdx).size(); }

		inline Element* getElement(ushort streamIdx, unsigned element)
		{ return &mElements.at(streamIdx).at(element); }

		unsigned getTypeSize(ElementType type) const;
	private:
		//TODO: Remove vector
		std::vector<std::vector<Element> > mElements;
	};
}

#endif /* RAVVERTEXDECLARION_H_INLCUDED */
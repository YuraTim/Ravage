#ifndef RAVARCSTRUCTS_H_INCLUDED
#define RAVARCSTRUCTS_H_INCLUDED

#include  "RavBase.h"

namespace Ravage
{
	const char RAV_ARC_HEADER_MAGIC[] = "@RAVARC0";

#pragma pack(1)
	struct ArcHeader
	{
		char     magic[8];    //Always RAV_ARC_HEADER_MAGIC.
		unsigned version;     //Current "1".
		unsigned size;        //Size of this header.

		unsigned id;          //Arc id.
		unsigned entryNumber; //Number of entries.
		bool isCompressed;    //Compression flag.
		bool isCrypted;       //Cryption flag.
		bool hasEntries;      //Location of entries (in exe or in arc)
		bool hasAttributes;   //Location of attributes (in exe or in arc)
		unsigned hash;        //Arc checksum
	};

	struct ArcEntry
	{
		unsigned id;       //Current ID
		unsigned parent;   //Parent ID
		unsigned offset;   //Offset of file container
		unsigned size;     //Size of file container
		unsigned arcId;    //Id of arc
		unsigned checksum; //File checksum
	};
#pragma pack()

	struct ArcAttribute
	{
		unsigned id;      //Attribute ID
		unsigned charset; //'A' - ANSI, 'U' - unicode
		String filename;

		unsigned reserved0; //Always 0
		unsigned reserved1; //Always 0
		unsigned reserved2; //Always 0
		unsigned reserved3; //Always 0
	};
}

#endif /* RAVARCSTRUCTS_H_INCLUDED */
#ifndef RAVFILEMODES_H_INCLUDED
#define RAVFILEMODES_H_INCLUDED

namespace Ravage
{
	enum FileMode
	{
		RAV_FMODE_READ  = 1,
		RAV_FMODE_WRITE = 2,
		RAV_FMODE_TEXT  = 4
	};

	enum FileSeekMode
	{
		RAV_SEEK_BEGIN = 0,
		RAV_SEEK_CUR   = 1,
		RAV_SEEK_END   = 2
	};

	enum FileFlags
	{
		RAV_FFLAG_TEXT    = 1,
		RAV_FFLAG_BINARY  = 2,
		RAV_FFLAG_OPENED  = 4,
		RAV_FFLAG_END     = 8,
		RAV_FFLAG_ANSI    = 16
	};
}

#endif /* RAVFILEMODES_H_INCLUDED */
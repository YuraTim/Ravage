#ifndef RAVLIST_H_INCLUDED
#define RAVLIST_H_INCLUDED

/* PART OF RAVAGE BASE */

namespace Ravage
{
    template <typename Type>
    struct List
    {
		explicit inline List(List* n = 0, List* p = 0) :
			next(n),
			prev(p)
		{
			if (n)
				n->prev = this;
			if (p)
				p->next = this;
		}

        explicit inline List(const Type& d, List* n = 0, List* p = 0) :
            data(d),
            next(n),
            prev(p)
        {
            if (n)
                n->prev = this;
			if (p)
				p->next = this;
        }

        Type  data;
        List* next;
        List* prev;

        inline void remove()
        {
            if (prev)
                prev->next = next;
            if (next)
                next->prev = prev;
        }

        inline bool isLast()
        { return next == 0; }

		inline bool isFirst()
		{ return prev == 0; }

        //inline int isNull()
        //{ return data == 0; }
    };
}

#endif // RAVLIST_H_INCLUDED

#ifndef RAVSTACK_H_INCLUDED
#define RAVSTACK_H_INCLUDED

#include <string.h>
#include <assert.h>

/* PART OF RAVAGE BASE */

namespace Ravage
{
	template <typename Type>
	class Stack
	{
	public:
		inline Stack() :
			mStack(new Type[1]),
			mSize(0),
			mCapacity(1)
		{}

		inline ~Stack()
		{ delete[] mStack; }

		inline void push(const Type& el)
		{
			if (mSize >= mCapacity)
			{
				Type* newbuf = new Type[mCapacity *= 2];
				memcpy(newbuf, mStack, sizeof(Type) * mSize);
				delete mStack;
				mStack = newbuf;
			}

			mStack[mSize++] = el;
		}

		inline Type& top()
		{ 
			assert(mSize > 0);
			return mStack[mSize - 1]; 
		}

		inline const Type& top() const
		{
			assert(mSize > 0);
			return mStack[mSize - 1];
		}

		inline void pop()
		{
			assert(mSize > 0);
			--mSize;
		}

		inline bool empty() const
		{ 
			return mSize == 0;
		}

		inline int size() const
		{
			return mSize;
		}
	private:
		//TODO: implement
		Stack(const Stack& stack);
		Stack& operator= (const Stack& stack);

	private:
		Type* mStack;
		int   mSize;
		int   mCapacity;
	};
}

#endif /* RAVSTACK_H_INCLUDED */
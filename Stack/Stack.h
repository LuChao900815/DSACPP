#ifndef __STACK_H__
#define __STACK_H__
#ifdef USE_VECTOR
#include "../Vector/Vector.h"
#else
#include "../List/List.h"
#endif

namespace dsacpp
{
#ifdef USE_VECTOR
	template <typename T>
	class Stack : public Vector<T>
	{
	public:
		void push(const T& e)
		{
			insert(size(),e)
		}
		T pop() 
		{
			return remove(size() - 1)
		}
		T& top()
		{
			return (*this)[size() - 1];
		}
	};
#else
	template <typename T>
	class Stack : public  List<T>
	{
	public:
		void push(const T& e)
		{
			insertAsLast(e);
		}
		T pop()
		{
			return remove(last())
		}
		T& top()
		{
			return last()->data;
		}
	};
#endif
}
#endif //__STACK__
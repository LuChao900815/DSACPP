#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "../List/List.h"




namespace dsacpp
{
	template <typename T>
	class Queue : public List<T>
	{
	public:
		void enqueue(const T& e)
		{
			insertAsLast(e);
		}
		T dequeue(void)
		{
			return  remove(first());
		}
		T& front() 
		{
			return  first()->data;
		}
	};
}
#endif //

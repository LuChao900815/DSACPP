#ifndef __VECTOR_H_
#define __VECTOR_H_
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include "../fundamental/fib.h"

namespace dsacpp
{
	//常量  
	typedef int Rank;
	#define CAPACITY 3 

	template <typename T>
	class Vector
	{
	public:
		//缺省构造函数
		Vector(Rank capacity = CAPACITY,Rank s = 0,T v = 0) : capacity_(capacity),size_(s)
		{
			T* elem_ = new T[capacity_];
			for(int i = 0; i < capacity; ++i)
			{
				elem_[i] = v;
			}
		}
		//数组构造函数
		Vector(const T* A, Rank lo,Rank hi)
		{
			copyFrom(A,lo,hi);
		}
		Vector(const T* A,Rank n)
		{
			copyFrom(A,0,n);
		}

		Vector(const Vector<T>& V)
		{
			delete[] elem_;
			copyFrom(V.elem_,0,V.size_);
		}

		Vector(const Vector<T>& V,Rank lo,Rank hi)
		{
			delete[] elem_;
			copyFrom(V.elem_,lo,hi);
		}

		//赋值构造函数
		Vector& operator=(const Vector<T>& v)
		{
			if(&v == this)
			{
				return *this;
			}
			if(elem_)
			{
				delete []elem_;
			}
			copyFrom(v.elem_,0,v.size_);
			return *this;
		}

		//析构函数
		~Vector()
		{
			delete []elem_;
		}
		//获取大小
		int size() const
		{
			return size_;
		}

		//判空
		bool empty() const
		{
			return size_ == 0;
		}

		//重载下标运算符
		T& operator[](const Rank position) const
		{
			assert(position >= 0 && position < size_);
			return elem_[postion];
		}

		//置乱器
		void permute(Vector<T>& v);

		//区间置乱器
		void unsort(const Rank lo, const Rank hi);

		//无序查找
		Rank find(const T& e,Rank lo, Rank hi);
		Rank find(const T& e);

		//插入
		Rank insert(Rank r,const T& e);

		//删除
		int remove(Rank lo,Rank hi);
		T remove(Rank r);

		//唯一化
		int deduplicate();

		//遍历
		void traverse(void (*visit)(T& e));

		template<typename VST>
		void traverse(VST& visit);

		//有序性判断
		int disorder() const;

		//有序唯一化
		int uniquify_1();
		int uniquify();

		//有序查找
		Rank binSearch(const T& e,Rank lo,Rank hi) const;
		Rank fibSearch(const T& e,Rank lo,Rank hi) const;
		Rank search(const T& e,Rank lo,Rank hi) const
		{
			return (rand() % 2) ? 
				binSearch(e,lo,hi) : fibSearch(e,lo,hi);
		}

		//排序
		void sort(Rank lo,Rank hi)
		{
			switch(rand() % 3)
			{
			case 1:
				bubbleSort(lo,hi);
				break;
			case 2:
				selectionSort(lo,hi);
				break;
			case 3:
				mergeSort(lo,hi);
				break;
			default:
				bubbleSort(lo,hi);
			}
		}


    //method 
	protected:
		void copyFrom(const T* A, int lo,int hi)
		{
			elem_ = new T[capacity_ = ((hi - lo) << 1)];
			size_ = 0;
			while(lo < hi)
			{
				elem_[size_++] = A[lo++];
			}
		}
	private:
		//扩容
		void expand();
		//缩容
		void shrink();
		//冒泡排序
		bool bubble_1(Rank lo,Rank hi);
		int  bubble(Rank lo,Rank hi);
		void bubbleSort(Rank lo,Rank hi);
		//选择排序
		Rank selection(Rank lo,Rank hi);
		void selectionSort(Rank lo,Rank hi);
		//归并排序
		void merge(Rank lo,Rank mi,Rank hi);
		void mergeSort(Rank lo,Rank hi);
	//data
	protected:
		T* elem_;
		int capacity_;
		int size_;
	};

	//扩容，以2倍形式扩容 
	template <typename T>
	inline void Vector<T>::expand()
	{
		if(size_ < capacity_)
		{
			return;
		}

		capacity_ = capacity_ > CAPACITY ? capacity_ : CAPACITY;

		T* oldElem = elem_;
		elem_ = new T[capacity_ <<= 1];

		for(int i = 0; i < size_; ++i)
		{
			elem_[i] = oldElem[i]; 
		}

		delete []oldElem;
	}

	//缩容
	template <typename T>
	inline void Vector<T>::shrink()
	{
		if(capacity_ < CAPACITY)
		{
			return;
		}

		if(size_ << 2 > capacity_)
		{
			return;
		}

		T*oldElem = elem_;
		elem_ = new T[capacity >>= 1];
		for(int i = 0; i < size_; ++i)
		{
			elem_[i] = oldElem[i];
		}
		delete []oldElem_;
	}

	//置乱器
	template <typename T>
	inline void  Vector<T>::permute(Vector<T>& v)
	{
		for(int i = v.size(); i > 0; i--)
		{
			std::swap(v[i - 1],v[rand() % i]);
		}
	}

	//区间置乱器
	template <typename T>
	inline void Vector<T>::unsort(const Rank lo,const Rank hi)
	{
		T* v = _elem + lo;
		for(Rank i = hi - lo; i > 0; i--)
		{
			std::swap(v[i - 1],v[rand() % i]);
		}
	}

	//无序查找
	template <typename T>
	inline Rank Vector<T>::find(const T& e,Rank lo,Rank hi)
	{
		while( (lo < hi--) && (e != elem_[hi]))
			;
		return hi;
	}

	template <typename T>
	inline Rank Vector<T>::find(const T& e)
	{
		find(e,0,size_);
	}

	//插入
	template <typename T>
	inline Rank insert(Rank r,const T& e)
	{
		expand();
		for(int i = size_; i > r; i--)
		{
			elem_[i] = elem_[i-1];
		}
		elem_[r] = e;
		size_++;
		return r;
	}

	//删除
	template <typename T>
	inline int Vector<T>::remove(Rank lo,Rank hi)
	{
		int oldSize = size_;
		if(lo >= hi)
		{
			return  0;
		}
		while(hi < size_)
		{
			elem_[lo++] = elem_[hi++];
		}
		size_ = lo;
		shrink();
		return odlSize - size_;
	}

	template <typename T>
	inline T Vector<T>::remove(Rank r)
	{
		T e = elem_[r];
		remove(r,r+1);
		return e;
	}

	//无序唯一化
	template <typename T>
	inline int Vector<T>::deduplicate()
	{
		int oldSize = size_;
		for(int i = 1; i < size_; ++i)
		{
			if(find(elem_[i],0,i) != -1)
			{
				remove(i);
			}
		}
		return oldSize - size_;
	}

	//遍历
	template<typename T>
	void Vector<T>::traverse(void (*visit)(T& e))
	{
		for(int i = 0; i < size_; ++i)
		{
			traverse(elem_[i]);
		}
	}

	template <typename T>
	template <typename VST>
	void Vector<T>::traverse(VST& visit)
	{
		for(int i = 0; i < size_; ++i)
		{
			traverse(elem_[i]);
		}
	}

	//有序性判断
	template <typename T>
	int Vector<T>::disorder() const
	{
		int n = 0;
		for(Rank i = 1; i < size_; ++i)
		{
			if(elem_[i - 1] > elem_[i])
			{
				++n;
			}
		}
		return n;
	}

	//有序唯一化
	template <typename T>
	int Vector<T>::uniquify_1()
	{
		int oldSize = size_;
		int i = 1;
		while(i < size_)
		{
			elem_[i - 1] == elem_[i] ? remove(i) : ++i;
		}
		return oldSize - size_;
	}

	template <typename T>
	int Vector<T>::uniquify()
	{
		Rank i = 0, j = 0;
		while(++j < size_)
		{
			if(elem_[i] != elem[j])
			{
				elem_[++i] = elem_[j];
			}
		}
		size_ = ++i;
		shrink();
		return j - i; 
	}

	template <typename T>
	Rank Vector<T>::binSearch(const T& e, Rank lo,Rank hi) const
	{
	#define C 
	#ifdef A
		while(lo < hi)
		{
			Rank mi = (hi + lo) >> 1;
			if(e < elem_[mi])
			{
				hi = mi;
			}
			else if(elem_[mi] < e)
			{
				lo = mi;
			}
			else
			{
				rerturn mi;
			}
		}
		return -1;
	#endif
	#ifdef B
		while(hi - lo > 1)
		{
			Rank mi = (hi + lo) >> 1;

			(e < A[mi]) ? hi = mi : lo = mi;
		}
		return (e == A[lo]) ? lo : -1;
	#endif
	#ifdef C
		while(hi - lo > 0)
		{
			Rank mi = (hi + lo) >> 1;

			(e < A[mi]) ? hi = mi : lo = mi + 1;
		}
		return --lo;
	#endif
	#undef C
	}

	//fib查找
	template <typename T>
	Rank Vector<T>::fibSearch(const T& e, Rank lo,Rank hi) const
	{
		DSCPP::Fib fib(hi - lo);
		while(lo < hi)
		{
			while(hi - lo < fib.get())
			{
				fib.prev();
			}
			Rank mi = lo + fib.get() - 1;
			if(e < elem_[mi])
			{
				hi = mi;
			}
			else if(elem_[mi] < e)
			{
				lo = mi + 1;
			}
			else
			{
				return  mi;
			}
		}
		return -1;
	}

	//冒泡排序
	template <typename T>
	inline bool Vector<T>::bubble_1(Rank lo,Rank hi)
	{
		bool sorted = true;
		while(++lo < hi)
		{
			if(elem_[lo - 1] > elem_[lo] )
			{
				sorted = false;
				std::swap(elem_[lo-1],elem_[lo])
			}
		}
		return sorted;
	}
	template <typename T>
	inline int Vector<T>::bubble(Rank lo,Rank hi)
	{
		Rank last = lo;
		while(++lo < hi)
		{
			if(elem_[lo - 1] > elem_[lo] )
			{
				last = lo;
				std::swap(elem_[lo-1],elem_[lo])
			}
		}
		return last;
	}
	template <typename T>
	inline void Vector<T>::bubbleSort(Rank lo,Rank hi)
	{
    #define V2
	#ifdef V1
		while(!bubble_1(lo,hi--));
	#endif 
	#ifdef V2
		while(lo < (hi = bubble(lo,hi)));
	#endif 
	#undef V2
	}

	//选择排序
	template <typename T>
	Rank Vector<T>::selection(Rank lo,Rank hi) //find the max in [lo,hi]
	{
		Rank index= lo;
		for(Rank i = lo + 1; i <= hi; ++i)
		{
			if( elem_[index] < elem_[i])
			{
				index = i;
			}
		}
		return index;
	}
	template <typename T>
	void Vector<T>::selectionSort(Rank lo,Rank hi)
	{
		while(lo < --hi)
		{
			std::swap(elem_[hi],elem_[selection(lo,hi)])
		}
	}

}
#endif //__VECTOR_H_
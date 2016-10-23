#ifndef __LIST_H__
#define __LIST_H__

#include "listNode.h"
#include <cstdlib>

namespace dsacpp
{
	typedef int Rank;
	template <typename T>
	class List
	{
	//data
	private:
		int size_;
		ListNodePosi(T) header;//头哨兵
		ListNodePosi(T) trailer;//尾哨兵
	//protected methods
	protected:
		void init(); 
		int clear();
		void copyNodes(ListNodePosi(T),int);
		void insertionSort(ListNodePosi(T),int);
		void selectionSort(ListNodePosi(T),int);

	//public methods
	public:
		List() {init();}
		List(const List<T>& L);
		List(const List<T>& L,Rank r,int n);
		List(ListNodePosi(T) p,int n);

		~List();
		//数量
		Rank size() const {return size_;}
		//判空
		bool empty() const {return size_ <= 0;}
		//不支持
		T& operator[](Rank index);
		//首元素
		ListNodePosi(T) first() const {return header->succ;}
		//末元素
		ListNodePosi(T) last() const  {return trailer->pred;}
		//判断指针是否有效
		bool valid(ListNodePosi(T) p)
		{
			return  p && (trailer != p) && (header != p);
		}
		//无序个数
		int disorder() const;
		//无序列表查找
		ListNodePosi(T) find(const T& e) const;
		ListNodePosi(T) find(const T& e,int n,ListNodePosi(T) p) const;
		//有序列表查找
		ListNodePosi(T) search(const T& e) const;
		ListNodePosi(T) search(const T& e,int n,ListNodePosi(T) p) const;
		//在列表查找最大值
		ListNodePosi(T) selectMax(ListNodePosi(T) p,int n);
		ListNodePosi(T) selectMax();
		//插入
		ListNodePosi(T) insertAsFirst(const T& e);
		ListNodePosi(T) insertAsLast(const T& e);
		ListNodePosi(T) insertAfter(ListNodePosi(T) p,const T& e);
		ListNodePosi(T) insertBefore(ListNodePosi(T) p,const T& e);
		//删除
		T remove(ListNodePosi(T) p);
		//排序
		void sort(ListNodePosi(T) p,int n);
		void sort() {sort(header->succ,size_);}
		//有序去重
		int deduplicate(); 
		//无序去重
		int uniquify(); 
		//反转列表
		void reverse();
		//遍历
		void traverse(void(*visit)(T&));
		template <typename VST>
		void traverse(VST& visit);
	};

	//初始化
	template <typename T>
	void List<T>::init()
	{
		size_ = 0;
		header = new ListNode<T>(0);
		trailer = new ListNode<T>(0,header);
		header->succ = trailer;
	}
	//清除列表中的元素
	template <typename T>
	int List<T>::clear()
	{
		int oldSize = size_;
		while(0 < size_)
		{
			remove(header->succ);
		}
		return oldSize;
	}
	//拷贝节点
	template <typename T>
	void List<T>::copyNodes(ListNodePosi(T) p,int n)
	{
		init();
		while(n-- > 0)
		{
			insertAsLast(p->data);
			p = p->succ;
		}
	}
	//插入排序
	template <typename T>
	void List<T>::insertionSort(ListNodePosi(T) p,int n)
	{
		for(int i = 0; i < n; ++i)
		{
			insertAfter(search(p->data,i,p),p->data);
			p = p->succ;
			remove(p->pred);
		}
	}
	//选择排序
	template <typename T>
	void List<T>::selectionSort(ListNodePosi(T) p,int n)
	{
		ListNodePosi(T) head = p->pred;
		ListNodePosi(T) tail = p;
		for(int i = 0; i < n; ++i)
		{
			tail = tail->succ;
		}

		while(1 < n)
		{
			ListNodePosi(T) max = selectMax(head->succ,n);
			insertBefore(tail,remove(max));
			tail = tail->pred;
			--n;
		}
	}
	//构造函数
	template <typename T>
	List<T>::List(const List<T>& L)
	{
		copyNodes(L.first(),L.size());
	}
	template <typename T>
	List<T>::List(const List<T>& L,Rank r,int n)
	{
		ListNodePosi(T) p = L.first();
		for(int i = 0; i < r; ++i)
		{
			p = p->succ;
		}
		copyNodes(p,n);
	}
	template <typename T>
	List<T>::List(ListNodePosi(T) p,int n)
	{
		copyNodes(p,n);
	}

	//析构函数
	template <typename T>
	List<T>::~List()
	{
		clear();
		delete header;
		delete trailer;
	}

	//operator []
	template <typename T>
	T& List<T>::operator[](Rank index)
	{
		ListNodePosi(T) p = first();
		for(int i = 0; i < index; ++i)
		{
			p = p->succ;
		}
		return p->data;
	}

	//无序个数
	template <typename T>
	int List<T>::disorder() const
	{
		ListNodePosi(T) head = first();
		int n = 0;
		while(head != trailer->pred)
		{
			if(head->data > (head->succ)->data)
			{
				++n;
			}
		}
		return n;
	}

	//无序列表查找
	template <typename T>
	ListNodePosi(T) List<T>::find(const T& e) const
	{
		return find(e,size_,trailer);
	}
	template <typename T>
	ListNodePosi(T) List<T>::find(const T& e,int n,ListNodePosi(T) p) const
	{
		while(n-- > 0)
		{
			if((p = p->pred)->data == e)
			{
				return p;
			}
		}
		return NULL;
	}
	//有序列表查找
	template <typename T>
	ListNodePosi(T) List<T>::search(const T& e) const
	{
		return search(e,size_,trailer);
	}
	template <typename T>
	ListNodePosi(T) List<T>::search(const T& e,int n,ListNodePosi(T) p) const
	{
		while(n-- >= 0)
		{
			if((p = p->pred)->data > e)
			{
				break;
			}
		}
		return p;
	}

	//在列表查找最大值
	template <typename T>
	ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p,int n)
	{
		ListNodePosi(T) max  = p;
		for(ListNodePosi(T) cur = p; 1 < n; n--)
		{
			if((cur = cur->succ)->data > max->data)
			{
				max = cur;
			}
		}
		return  max;
	}
	template <typename T>
	ListNodePosi(T) List<T>::selectMax()
	{
		return selectMax(first(),size_);
	}
	//插入
	template <typename T>
	ListNodePosi(T) List<T>::insertAsFirst(const T& e)
	{
		size_++;
		return header->insertAsSucc(e);
	}
	template <typename T>
	ListNodePosi(T) List<T>::insertAsLast(const T& e)
	{
		size_++;
		return trailer->insertAsPred(e);
	}
	template <typename T>
	ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p,const T& e)
	{
		size_++;
		return p->insertAsSucc(e);
	}
	template <typename T>
	ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p,const T& e)
	{
		size_++;
		return p->insertAsPred(e);
	}

	//删除
	template <typename T>
	T List<T>::remove(ListNodePosi(T) p)
	{
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		T e = p->data;
		size_--;
		delete p;
		return e;
	}
	//排序
	template <typename T>
	void List<T>::sort(ListNodePosi(T) p,int n)
	{
		switch(rand() % 2)
		{
		case 0:
			insertionSort(p,n);
			break;
		default:
			selectionSort(p,n);
			break;
		}
	}
	//有序去重
	template <typename T>
	int List<T>::deduplicate()
	{
		int oldSize = size_;
		ListNodePosi(T) head = first();
		int r = 1;
		while((head = head->succ) != trailer)
		{
			ListNodePosi(T) p = find(head->data,r,head) ;
			p == NULL ? r++ : remove(p);
		}
		return oldSize - size_;
	}
	//无序去重
	template <typename T>
	int List<T>::uniquify()
	{
		int oldSize = size_;
		ListNodePosi(T) head = first();
		ListNodePosi(T) q = NULL;
		while((q = head->succ) != trailer)
		{
			if(head->data != q->data)
			{
				head = q;
			}
			else
			{
				remove(q);
			}
		}
		return  oldSize - size_;
	}
	//反转列表
	template <typename T>
	void List<T>::reverse()
	{
		ListNodePosi(T) head = first();
		ListNodePosi(T) tail = last();
		while(head != tail)
		{
			std::swap(head->data,tail->data);
			head = head->succ;
			tail = tail->pred;
		}
	}
	//遍历
	template <typename T>
	void List<T>::traverse(void(*visit)(T&))
	{
		ListNodePosi(T) head = first();
		while(head != trailer)
		{
			visit(head->data);
			head = head->succ;
		}
	}
	template <typename T>
	template <typename VST>
	void List<T>::traverse(VST& visit)
	{
		ListNodePosi(T) head = first();
		while(head != trailer)
		{
			visit(head->data);
			head = head->succ;
		}
	}

}


#endif //__LIST_H__
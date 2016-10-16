#ifndef __LIST_NODE_H__
#define __LIST_NODE_H__
#include <cstdlib>
namespace dsacpp
{
	typedef int Rank;
	#define ListNodePosi(T) ListNode<T>*
	template <typename T>

	//节点类
	struct ListNode
	{
		//member data
		T data;
		ListNodePosi(T) pred;
		ListNodePosi(T) succ;
		//member method
		ListNode(){}
		ListNode(T e,ListNodePosi(T) p = NULL,ListNodePosi(T) s = NULL)
			: data(e),pred(p),succ(s){}

		//method 
		ListNodePosi(T) insertAsPred(const T& e);
		ListNodePosi(T) insertAsSucc(const T& e);
	};
	template <typename T>
	ListNodePosi(T) ListNode<T>::insertAsPred(const T& e)
	{
		ListNodePosi(T) newElem = new ListNode<T>(e,pred,this);
		pred->succ = newElem;
		this->pred = newElem;
		return newElem;
	}
	template <typename T>
	ListNodePosi(T) ListNode<T>::insertAsSucc(const T& e)
	{
		ListNodePosi(T) newElem = new ListNode<T>(e,this,succ);
		this->succ->pred = newElem;
		this->succ = newElem;
		return newElem;
	}

}

#endif //__LIST_NODE_H__
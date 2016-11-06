#ifndef __BINTREE_H__
#define __BINTREE_H__

#include "BinNode.h"

namespace dsacpp
{
	template <typename T>
	class BinTree
	{
	protected:
		int size_;
		BinNodePosi(T) root_;
		virtual int updateHeight(BinNodePosi(T) x);
		void updateHeightAbove(BinNodePosi(T) x);

	public:
		BinTree() : size_(0),root_(NULL){}
		~BinTree() 
		{
			if (0 < size_) 
			{
				remove(root_);
			}
		}
		int size() const 
		{
			return size_;
		}
		bool empty() const
		{
			return size_ == 0;
		}
		BinNodePosi(T) root() const
		{
			return root_;
		}
		BinNodePosi(T) insertAsRoot(const T& e);
		BinNodePosi(T) insertAsLChild(BinNodePosi(T) x,const T& e);
		BinNodePosi(T) insertAsRChild(BinNodePosi(T) x,const T& e);
		BinNodePosi(T) attachAsLC(BinNodePosi(T) x,BinTree<T> &T);
		BinNodePosi(T) attachAsRC(BinNodePosi(T) x,BinTree<T> &T);
		int remove(BinNodePosi(T) x);
		BinTree<T>* secede(BinNodePosi(T) x);
		template <typename VST> 
		void travLevel(VST&)
		{
			root_->travLevel(VST);
		}
		template <typename VST> 
		void travPre(VST&)
		{
			root_->travPre(VST);
		}
		template <typename VST> 
		void travIn(VST&)
		{
			root_->travIn(VST);
		}
		template <typename VST> 
		void travPost(VST&)
		{
			root_->travPost(VST);
		}
		bool operator<(BinTree<T>& bn)
		{
			return root_ && root_ < bn.root_;
		}
		bool operator==(BinTree<T>& bn)
		{
			return root_ && root_ == bn.root_;
		}
	};
}


#endif //__BINTREE_H__
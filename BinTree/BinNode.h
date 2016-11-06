#ifndef __BINNODE_H__
#define __BINNODE_H__

namespace dsacpp
{
	#define BinNodePosi(T) NinNode<T>*
	#define stature(p) ((p) ? (p)->height : -1)
	typedef enum {RB_RED,RB_BLACK}RBColor; //红黑树

	//关系
	#define IsRoot(x)		(!((x).parent))
	#define IsLChild(x)		(!IsRoot(x) && (x).parent->lChild == &(x))
	#define IsRChild(x)     (!IsRoot(x) && (x).parent->rChild == &(x)) 
	#define HasParent(x)    (!IsRoot(x))
	#define HasLChild(x)	((x).lc)
	#define HasRChild(x)	((x).rc)
	#define HasChild(x)		((HasLChild) || (HasRChild))
	#define HasBothChild(x) ((HasLChild) && (HasRChild))
	#define IsLeaf(x)		(!HasChild(x))

	template <typename T>
	class BinNode
	{
	public:
		//data
		T data;
		BinNodePosi(T) lChild,parent,rChild;
		int height;//高度
		int npl;//Null Path Length（左式堆，也可直接用height代替）
		RBColor color;//红黑树的颜色
		//methods
		BinNode() :
			parent(NULL),lChild(NULL),rChild(NULL),height(0),npl(1),color(RB_RED){}
		BinNode(T e,BinNodePosi(T) p = NULL,BinNodePosi(T) l = NULL, 
			BinNodePosi(T) r = NULL,int h = 0,int n = 1, RBColor c = RB_RED) :
				data(e),parent(p),lChild(l),rChild(r),height(h),npl(n),color(c){}
		int size();
		BinNodePosi(T) insertAsLChild(const T&);
		BinNodePosi(T) insertAsRChild(const T&);
		BinNodePosi(T) succ();
		template <typename VST> void travLevel(VST&);
		template <typename VST> void travPre(VST&);
		template <typename VST> void travIn(VST&);
		template <typename VST> void travPost(VST&);

		bool operator<(const BinNode& bn) const {return data < bn.data;}
		bool operator==(const BinNode& bn) const {return data == bn.data;}
	};

	//获取后代的数量
	template <typename T>
	inline int BinNode<T>::size()
	{
		int s = 1;
		if(lChild) s += lChild->size();
		if(rChild) s += rChild->size();
		return s;
	}

	//插入左孩子
	template <typename T>
	inline BinNodePosi(T) BinNode<T>::insertAsLChild(const T& e)
	{
		return lChild = new BinNode(e,this);
	}

	//插入右孩子
	template <typename T>
	inline BinNodePosi(T) BinNode<T>::insertAsRChild(const T& e)
	{
		return rChild = new BinNode(e,this);
	}
	 
	//后继
	template <typename T>
	inline BinNodePosi(T) BinNode<T>::succ()
	{
		if(rChild)
		{
			BinNodePosi(T) s = rChild;
			while(HasLChild(s))
			{
				s = s->lChild;
			}
			return s;
		}
		else
		{
			BinNodePosi(T) self = this;
			while(IsRChild(*self))
			{
				self = self->parent;
			}
			return self->parent;
		}
	}

	
}
#endif // __BINNODE_H__
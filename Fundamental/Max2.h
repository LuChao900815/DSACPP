#ifndef __MAX2_H_
#define __MAX2_H_

void max2(int A[],int lo, int hi,int& x1,int& x2)
{
	for(int i = lo; i < hi; ++i)
	{
		if(A[i] > A[x1])
		{
			x1 = i;
		}
	} // 得到x1

	for(int i = lo; i < x1; ++i)
	{
		if(A[i] > A[x2])
		{
			x2 = i;
		}
	}//在[lo,x1) 找最大值

	for(int i = x1 + 1; i < hi; ++i)
	{
		if(A[i] > A[x2])
		{
			x2 = i;
		}
	}//在[x1+1,,hi) 找最大值
	//O(2n-3)
}

//
void max2I(int A[],int lo, int hi,int& x1,int& x2)
{
	if(A[x1=lo] < A[x2=lo+1])
	{
		swap(x1,x2);
	}

	for(int i = lo + 2; i < hi; ++i)
	{
		if(A[i] > A[x2])
		{
			if(A[x2 = i] > A[x1])
			{
				swap(x1,x2);
			}
		}
	}

	//best: O(n-1)
	//bad: O(2n-3)
}

void max2R(int A[],int lo,int hi,int& x1, int& x2)
{
	if(lo + 2 == hi)
	{
		x1 = lo;
		x2 = lo + 1;
		if(A[x1] < A[x2])
		{
			swap(x1,x2);
		}
		return;
	}
	if(lo + 3 == hi)
	{
		x1 = lo;
		x2 = lo + 1;
		if(A[x1] > A[x2])
		{
			if(A[x2] < A[lo + 2])
			{
				x2 = lo + 2;
			}
		}
		else 
		{
			if(A[x1] < A[lo + 2])
			{
				x1 = lo + 2;
			}
		}

		if(A[x1] < A[x2])
		{
			swap(x1,x2);
		}
		return;
	}

	int mi = (lo + hi) >> 1;
	int x1L,x1R,x2L,x2R;
	max2R(A,lo,mi,x1L,x2L);
	max2R(A,mi,hi,x1R,x2R);

	if(A[x1L] > A[x1R])
	{
		x1 = x1L; x2 = (A[x2L] > A[x1R] ? x2L : x1R);
	}
	else
	{
		x1 = x1R; x2 = (A[x1L] > A[x2R] ? x1L : x2R);
	}
	//T(n) = 2 * T(n/2) + 2 <= 5n/3 - 2
}
#endif // __MAX2_H_

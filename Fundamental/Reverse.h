#ifndef __REVERSE_H_
#define __REVERSE_H_

void reverse(int* A,int lo,int high)
{
	if(lo < high)
	{
		swap(A[lo],A[high]);
		reverse(A,lo+1,high+1);
	}
}

void reverseI(int* A,int lo,int high)
{
	while(lo < high)
	{
		swap(A[lo++],A[high--]);
	}
}

#endif //__REVERSE_H_
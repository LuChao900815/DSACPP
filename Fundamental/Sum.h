#ifndef __SUM_H_
#define __SUM_H_

int SumI(int a[],int n)
{
	int sum = 0;
	for(int i = 0; i < n; i++)
		sum += a[i];
	return sum;
}

int sum(int A[],int n)
{
	return (n < 1 ? 0 : A[n-1] + sum(A,n-1));
}

int sumR(int A[],int lo,int hi)
{
	if(lo == hi)
		return A[lo];
	int mi = (lo  + hi) >> 1;
	return sumR(A,lo,mi) + sumR(A,mi + 1,hi);
}

#endif //__SUM_H_
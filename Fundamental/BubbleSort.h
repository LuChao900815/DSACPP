#ifndef __BUBBLESORT_H_
#define __BUBBLESORT_H_

void bubbleSort(int A[],int n)
{
	for(bool sorted = false; sorted = !sorted ; n--)
		for(int i = 1; i < n; ++i)
		{
			if(A[i-1] > A[i])
			{
				swap(A[i-1],A[i]);
				sorted = false;
			}
		}
}

#endif //__BUBBLESORT_H_
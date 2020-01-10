#include <iostream>
#include <conio.h>
using namespace std;

void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;

}

int partition(int a[], int low, int high)
{
	int i, j;
	i = low - 1;
	int pivot = a[high];
	for (j = low; j <= high - 1; j++)
	{
		if (a[j] < pivot)
		{
			++i;
			swap(&a[i], &a[j]);
		}
	
	}
	swap(&a[i + 1], &a[high]);
	return i + 1;
}
void quick(int a[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(a, low, high);
		quick(a, low, pi - 1);
		quick(a, pi + 1, high);
	}
}	
int main()
{
	int A[] = { 1,5,2,10,2,15,7,6 };
	int n = sizeof(A) / sizeof(A[0]);
	int beg = 0;
	int end = n - 1;
	quick(A, beg, end);
	for (int i = 0; i < n; i++)
	{
		cout << A[i];
	}
}
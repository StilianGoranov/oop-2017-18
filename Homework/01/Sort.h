#ifndef _SORT_H
#define _SORT_H

#include <algorithm>

class Sort
{
private:
	template <typename T>
	static int partition(T arr[], int l, int h)
	{
		T splitter = arr[h];
		int p = l;
		for (int i = l; i <= h - 1; ++i)
			if (arr[i] < splitter)
				std::swap(arr[i], arr[p++]);
		std::swap(arr[h], arr[p]);
		return p;
	}

public:

	template <typename T>
	static void quickSort(T arr[], int l, int h)
	{
		if (l < h)
		{
			int m = partition(arr, l, h);
			quickSort(arr, l, m - 1);
			quickSort(arr, m + 1, h);
		}
	}
};


#endif 

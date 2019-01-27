
#pragma once

#include <vector>
#include <cstddef>
#include <cmath>


namespace otusalg
{


template<typename T>
class heap
{
	std::vector<T> v;

public:
	heap(){}
	heap(heap &h) = delete;
	heap(heap &&h) = delete;

	~heap(){}

	std::size_t parent(std::size_t idx)
	{
		// return std::floor((idx - 1) / 2);
		return ((idx - 1) / 2);
	}

	std::size_t leftChild(std::size_t idx)
	{
		return idx * 2 + 1;
	}

	std::size_t rightChild(std::size_t idx)
	{
		return idx * 2 + 2;
	}

	void drown(int idx)
	{
		int x = idx;
		int largest = 0;
		int l = leftChild(x);
		int r = rightChild(x);

		while((l <= v.size()) && (r <= v.size()))
		{
			if(v[l] > v[r])
				largest = l;
			else
				largest = x;
			if(v[r] > v[largest])
				largest = r;
			if(largest != x)
			{
				std::swap(v[x], v[largest]);
				x = largest;
				l = leftChild(x);
				r = rightChild(x);
			}
			else
				break;

		}
	}


	void buildHeap(std::iterator first, std::iterator last)
	{
		
	}

}



} // namespace otusalg

1  Drown(Heap, i, size):  // (Пирамида, индекс, ограничения на массив)
2      l := Left(i)
3      r := Right(i)
4      if l ≤ size and Heap[l] > Heap[r]  // первая проверка - выход за пределы
5          largest := l
6      else 
7          largest := i   
8      if r ≤ size and Heap[r] > Heap[largest]
9          largest := r
10     if largest != i
11         Swap(Heap, i, largest)
12         Drown(Heap, largest, size)  // рекурсия



1  BuildHeap(Array):
2      for i := Floor((length(Array) - 1) / 2) downto 0
3          Drown(Array, i, size)
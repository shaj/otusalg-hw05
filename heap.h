
#pragma once

#include <vector>
#include <cstddef>
#include <cmath>
#include <iostream>

namespace otusalg
{


template<typename T>
class heap
{
	std::vector<T> v;

	void _buildHeap()
	{
	}

public:
	heap()
	{
		// v = std::make_unique(new std::vector<T>);
	}

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
				largest = r;

			if(v[x] >= v[largest])
				break;

			std::swap(v[x], v[largest]);
			x = largest;
			l = leftChild(x);
			r = rightChild(x);
		}
	}


	template<typename Iter>
	void buildHeap(Iter first, Iter last)
	{
		static_assert(std::is_same<typename std::iterator_traits<Iter>::value_type, T>::value, "Test");

		v.clear();
		std::copy(first, last, std::back_inserter(v));

		for(int i=((v.size() -1) / 2); i>=0; i--)
		{
			drown(i);
		}
	}


	void remove(int idx)
	{
		std::swap(v[idx], v[v.size()-1]);
		v.erase(v.end()-1);
		drown(idx);
	}


	void printHeap_dot(std::ostream &out)
	{
		int l;
		int r;

		out << "digraph g {\n";
		for(int i=0; i<v.size(); i++)
		{
			out << "\"" << v[i] << "\";\n";
			l = leftChild(i);
			r = rightChild(i);
			if(l < v.size())
				out << "\"" << v[i] << "\" -> \"" << v[l] << "\";\n";
			if(r < v.size())
				out << "\"" << v[i] << "\" -> \"" << v[r] << "\";\n";
		}
		out << "}\n";
	}

};



} // namespace otusalg


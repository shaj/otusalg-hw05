
#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>


namespace otusalg
{

template<typename T>
void gen_type1(std::size_t l, std::vector<T> &v)
{
	v.clear();
	v.reserve(l);
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(i);
	}

    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(v.begin(), v.end(), g);
}


template<typename T>
void gen_type2(std::size_t l, std::vector<T> &v)
{
	v.clear();
	v.reserve(l);
	std::srand(std::time(nullptr));
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(std::rand());
	}
}


template<typename T>
void gen_type3(std::size_t l, std::vector<T> &v)
{
	v.clear();
	v.reserve(l);
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(i);
	}
}



} // namespace otusalg


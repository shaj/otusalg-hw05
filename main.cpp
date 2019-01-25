
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>

#include "oa_sort.h"

// Отсюда
// https://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
							(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};



void read_data(std::istream &is, std::vector<int> &v)
{
	std::string slen;
	std::getline(is, slen);
	v.clear();
	v.reserve(std::stoi(slen));
	for(std::string line; std::getline(is, line);)
	{
		v.emplace_back(std::stoi(line));
	}
}

void test_vector(const std::vector<int> &v)
{
	int cnt = 0;
	for(auto it = v.begin() + 1; it != v.end(); it++)
	{
		if(*it < *(it-1)) cnt++;
	}
	if(cnt) std::cout << "array is NOT sorted\n";
	else std::cout << "array is sorted" << std::endl;
}

int main(int argc, char const *argv[])
{

	if(argc > 1)
	{
		std::cout << "'" << argv[1] << "'\n";

		std::vector<int> v;
		std::ifstream fs;
 	    fs.open(argv[1], std::ios::in);
 
	    if(fs.is_open())
	    {
	    	read_data(fs, v);
	    	fs.close();

	    	fs.open(argv[1]);
	    	read_data(fs, v);
	    	fs.close();
	    	std::cout << "std::sort: " << measure<std::chrono::microseconds>::execution([&]()
	    	{
	    		std::sort(v.begin(), v.end(), std::less<int>());
	    	}) << " us\n";
	    	test_vector(v);


	    }
	    else
	    {
	    	std::cout << "File '" << argv[1] << "' does not exist" << std::endl;
	    }
	}

	return 0;
}


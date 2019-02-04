
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>

#include "heap.h"
#include "generators.h"

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


int main(int argc, char const *argv[])
{


	{
		std::vector<int> vec;

		otusalg::gen_type1(18, vec);
		otusalg::heap<int> h;
		h.buildHeap(vec.begin(), vec.end());
		std::cout << "Из последовательности:\n";
		std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "\nсгенерирована куча. Структура записана в файл 'out1.dot'" << std::endl;

		std::ofstream fos("out1.dot");
		h.printHeap_dot(fos);
		fos.close();

		std::cout << "После удаления элемента 4, структура записана в файл 'out2.dot'\n" << std::endl;
		h.remove(4);

		fos.open("out2.dot");
		h.printHeap_dot(fos);
		fos.close();

		auto vvv = h.getSorted();
		std::cout << "Отсортировано:\n";
		std::copy(vvv.begin(), vvv.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;

		vvv = h.getSorted();
		std::cout << "Отсортировано:\n";
		std::copy(vvv.begin(), vvv.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}


	{
		std::vector<int> vec;
		otusalg::heap<int> h;

		otusalg::gen_type1(32768, vec);
		std::cout << "Для перемешанной последовательности из 32768 куча построена за " << measure<std::chrono::microseconds>::execution([&]()
			{
				h.buildHeap(vec.begin(), vec.end());
			}) << " us\n";

		otusalg::gen_type1(1048576, vec);
		std::cout << "Для перемешанной последовательности из 1048576 куча построена за " << measure<std::chrono::microseconds>::execution([&]()
			{
				h.buildHeap(vec.begin(), vec.end());
			}) << " us\n";
	}

	return 0;
}



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
		std::cout << "\n" << std::endl;
	}


	{
		std::cout << "\nПроверка remove\n";
		std::vector<int> v {
			100, 
			90, 
			50, 
			89, 88,
			49, 48, 
			87, 86, 85, 84, 
			47, 46, 45, 44, 
			83, 82, 81, 80, 79, 78, 77, 76, 
			43, 42, 41, 40, 39, 38, 37, 36, 
			75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60,
			35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,
			59, 58, 57, 56, 55
		};

		otusalg::heap<int> h;
		h.buildHeap(v.begin(), v.end());

		std::ofstream fos;

		fos.open("a1.dot");
		h.printHeap_dot(fos);
		fos.close();

		h.remove(27);

		fos.open("a2.dot");
		h.printHeap_dot(fos);
		fos.close();

		auto vvv = h.getSorted();
		if(std::is_sorted(vvv.begin(), vvv.end(), std::greater<int>())) std::cout << "vector sorted\n";
		else std::cout << "vector NOT sorted\n";
		std::cout << std::endl;

	}


	{
		std::vector<int> vec;
		otusalg::heap<int> h;
		std::vector<int> vvv;

		otusalg::gen_type1(32768, vec);
		std::cout << "Для перемешанной последовательности из 32768 куча построена за " << measure<std::chrono::microseconds>::execution([&]()
			{
				h.buildHeap(vec.begin(), vec.end());
			}) << " us\n";

		std::cout << "Сортировка " << measure<std::chrono::microseconds>::execution([&]()
			{
				vvv = std::move(h.getSorted());
			}) << " us\n";
		if(std::is_sorted(vvv.begin(), vvv.end(), std::greater<int>())) std::cout << "vector sorted\n";
		else std::cout << "vector NOT sorted\n";
		std::cout << std::endl;

		otusalg::gen_type1(1048576, vec);
		std::cout << "Для перемешанной последовательности из 1048576 куча построена за " << measure<std::chrono::microseconds>::execution([&]()
			{
				h.buildHeap(vec.begin(), vec.end());
			}) << " us\n";

		std::cout << "Сортировка " << measure<std::chrono::microseconds>::execution([&]()
			{
				vvv = std::move(h.getSorted());
			}) << " us\n";
		if(std::is_sorted(vvv.begin(), vvv.end(), std::greater<int>())) std::cout << "vector sorted\n";
		else std::cout << "vector NOT sorted\n";
		std::cout << std::endl;
	}

	return 0;
}


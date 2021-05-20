#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;
/*
template<typename It>
void PrintRange(It tbegin, It tend) {

	for (auto t = tbegin; t != tend; t++) {
		cout << *t << " ";
	}
	cout << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {


	if (range_end - range_begin > 1) {
		vector<typename iterator_traits<RandomIt>::value_type> buff(range_begin, range_end);

		RandomIt middle = buff.begin() + (buff.end() - buff.begin()) / 2;
		MergeSort(buff.begin(), middle);
		MergeSort(middle, buff.end());

		merge(buff.begin(), middle, middle, buff.end(), range_begin);

	}
}

int main() {
	vector<int> test_vector(10);

	// iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
	// Заполняет диапазон последовательно возрастающими значениями
	iota(test_vector.begin(), test_vector.end(), 1);

	// random_shuffle   -> https://ru.cppreference.com/w/cpp/algorithm/random_shuffle
	// Перемешивает элементы в случайном порядке
	random_shuffle(test_vector.begin(), test_vector.end());

	// Выводим вектор до сортировки
	PrintRange(test_vector.begin(), test_vector.end());

	// Сортируем вектор с помощью сортировки слиянием
	MergeSort(test_vector.begin(), test_vector.end());

	// Выводим результат
	PrintRange(test_vector.begin(), test_vector.end());

	return 0;
}
*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
/*
using namespace std::string_literals;
template <typename It>
void PrintRange(It range_begin, It range_end) {
	for (auto it = range_begin; it != range_end; ++it) {
		std::cout << *it << " "s;
	}
	std::cout << std::endl;
}
template <typename F, typename E>
void FindAndPrint(const F f, const E& elem) {
	auto it1 = find(f.begin(), f.end(), elem);
	PrintRange(f.begin(), it1);
	std::cout << std::endl;
	PrintRange(it1, f.end());
	std::cout << std::endl;
}
template <typename Container, typename It>
void EraseAndPrint(Container& container, It it) {
	it = container.erase(it);
	FindAndPrint(container, *it);
}
int main() {
	std::vector<std::string> langs = { "Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s };
	langs.erase(langs.begin());
	EraseAndPrint(langs, langs.begin());
}
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
/*
using namespace std;

// �������, ������������ �������� ��������� � ������
template <typename It>
string PrintRangeToString(It range_begin, It range_end) {
	// ������� ��� ostringstream -> https://ru.cppreference.com/w/cpp/io/basic_ostringstream
	ostringstream out;
	for (auto it = range_begin; it != range_end; ++it) {
		out << *it << " ";
	}
	out << endl;
	// �������� ������ � ������ � ������� ������ str ��� ostringstream
	return out.str();
}
template<typename It>
std::vector<std::string > GetPermutations(It it_begin, It it_end) 
{
	std::vector<std::string> res;
	do {
		res.push_back(PrintRangeToString(it_begin, it_end));
	} 
	while (next_permutation(it_begin, it_end));
	
	reverse(res.begin(),res.end());
	return res;
}

int main() {
	vector<int> permutation(3);
	// iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
	// ��������� �������� ��������������� ������������� ����������
	iota(permutation.begin(), permutation.end(), 1);

	auto result = GetPermutations(permutation.begin(), permutation.end());
	for (const auto& s : result) {
		cout << s;
	}
	return 0;
}
*/
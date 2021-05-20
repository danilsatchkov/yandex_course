#include <iostream>
#include<vector>
#include <string>
#include <algorithm>
using namespace std;
/*

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, string prefix) {
	// Все строки, начинающиеся с '<prefix>', больше или равны строке "<prefix>"
	auto left = lower_bound(range_begin, range_end, prefix);

	// Составим следующий в алфавите символ.
	// Не страшно, если prefix = 'z':
	//в этом случае мы получим следующий за 'z' символ в таблице символов
	//char next_prefix = static_cast<char>(prefix + 1);

	// Строка "<next_prefix>" в рамках буквенных строк
	// является точной верхней гранью
	// множества строк, начнающихся с '<prefix>'
	prefix.back() += 1;
	auto right = lower_bound(range_begin, range_end, prefix);

	return { left, right };
}



int main() {
	const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

	const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	cout << (mt_result.first - begin(sorted_strings)) << " " << (mt_result.second - begin(sorted_strings)) << endl;

	const auto na_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	cout << (na_result.first - begin(sorted_strings)) << " " << (na_result.second - begin(sorted_strings)) << endl;

	return 0;
}






string char_to_string(const char c)
{
	char cstr[2] = ""; //A C type string
	cstr[0] = c;

	return cstr;
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
	// напишите реализацию
	struct cmp {
		bool operator()(const std::string &s, char c) const { return s.front() < c; }
		bool operator()(char c, const std::string &s) const { return c<s.front(); }
	};
	
	auto [lower,upper] = std::equal_range(range_begin, range_end, prefix, cmp{});

	return make_pair(lower, upper);
}




int main() {
	const vector<string> sorted_strings = { "moscow", "murmansk", "vologda" };

	const auto m_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
	for (auto it = m_result.first; it != m_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto p_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
	cout << (p_result.first - begin(sorted_strings)) << " " << (p_result.second - begin(sorted_strings)) << endl;

	const auto z_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
	cout << (z_result.first - begin(sorted_strings)) << " " << (z_result.second - begin(sorted_strings)) << endl;

	return 0;
}

*/
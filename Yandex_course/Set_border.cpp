#include<set>
#include <algorithm>
#include <iostream>
using namespace std;
/*

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
	// set<int>::const_iterator — тип итераторов для константного множества целых чисел
	set<int>::const_iterator it_low,it_back, it_forth;
	//equal or higher
	it_low = numbers.lower_bound( border);
	if (numbers.empty()) return numbers.end();
	if (it_low == numbers.end()) return prev(it_low);
	//if not equal, take a step back
	if (*it_low != border) {
		it_back = prev(it_low);
		if (it_back != numbers.end()) {
			
			if (border - *it_back <= *it_low - border) return it_back;
			else return it_low;
		}
		
	}
	return it_low;



}

int main() {
	set<int> numbers = { 1, 4, 6 };
	
	cout << *FindNearestElement(numbers, 0) << " " << *FindNearestElement(numbers, 3) << " "
		<< *FindNearestElement(numbers, 5) << " " << *FindNearestElement(numbers, 6) << " "
		<< *FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
	return 0;
}
*/
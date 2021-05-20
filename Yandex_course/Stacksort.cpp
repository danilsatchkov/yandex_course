#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
/*
using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
	for (auto it = range_begin; it != range_end; ++it) {
		cout << *it << " ";
	}
	cout << endl;
}

template <typename Type>
class Stack {
public:
	void Push(const Type& element) {
		elements_.push_back(element);
	}
	void Pop() {
		elements_.pop_back();
	}
	const Type& Peek() const {
		return elements_.back();
	}
	Type& Peek() {
		return elements_.back();
	}
	void Print() const {
		PrintRange(elements_.begin(), elements_.end());
	}
	uint64_t Size() const {
		return elements_.size();
	}
	bool IsEmpty() const {
		return elements_.empty();
	}

	auto rbegin() const {
		return elements_.rbegin();
	}
	auto rend() const {
		return elements_.rend();
		}
	auto begin() const {
		return elements_.begin();
	}

private:
	vector<Type> elements_;
};

template <typename Type>
class SortedStack {
public:
	void Push(const Type& element) {
		// напишите реализацию метода
		if (elements_.IsEmpty()||element<elements_.Peek())
		{
			elements_.Stack::Push(element);
			return;
		}
		
		
		Stack<Type> temp;
		auto elements_copy = elements_;
		//for (auto it = elements_copy.rbegin(); it != elements_copy.rend(); ++it) 
		for (auto it = elements_copy.rbegin();it!=elements_copy.rend();++it)
		{
			if (element > *it) {
				//same temporare all values that are above current value
				temp.Stack::Push(*it);
				elements_.Pop();
			}

		}

		//if (elements_.IsEmpty() || element > *elements_.begin()) {
			elements_.Stack::Push(element);
			for (auto it = temp.rbegin();it!=temp.rend();++it)
			 {
				elements_.Stack::Push(*it);
			}	
		//}
		


	}

	void Pop() {
		// напишите реализацию метода
		elements_.Pop();
	}
	const Type& Peek() const {
		return elements_.Peek();
	}
	Type& Peek() {
		return elements_.Peek();
	}
	void Print() const {
		elements_.Print();
	}
	uint64_t Size() const {
		return elements_.Size();
	}
	bool IsEmpty() const {
		return elements_.IsEmpty();
	}
private:
	Stack<Type> elements_;
};

int main() {
	SortedStack<int> stack;
	vector<int> values(7);

	// заполняем вектор для тестирования нашего стека
	iota(values.begin(), values.end(), 1);
	cout << *max_element(values.begin(), values.end()) << endl;;
	// перемешиваем значения
	random_shuffle(values.begin(), values.end());
	cout << values[2] << endl;
	// заполняем стек и проверяем, что сортировка сохраняется после каждой вставки
	for (int i = 0; i < 7; ++i) {
		cout << "Вставляемый элемент = " << values[i] << endl;
		stack.Push(values[i]);
		stack.Print();
	}
}
*/
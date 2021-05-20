#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/*
using namespace std;

template <typename Type>
class StackMin {
public:
	void Push(const Type& element) {
		// напишите реализацию метода
		if (elements_.empty())
		{
			elements_.push_back({ element, element });
			return;
		}
		elements_.push_back({ element,min(element,PeekMin()) });
	}
	void Pop() {
		// напишите реализацию метода
		elements_.pop_back();
	}
	const Type& Peek() const {
		return elements_.Peek();
	}
	Type& Peek() {
		return elements_.Peek();
	}
	void Print() const {
		// работу этого метода мы проверять не будем,
		// но если он вам нужен, то можете его реализовать
		for (auto e : elements_) {
			cout << " " << e.first;

		}
		cout << endl;
	}
	uint64_t Size() const {
		return elements_.size();
	}
	bool IsEmpty() const {
		return elements_.empty();
	}
	const Type& PeekMin() const {
		// напишите реализацию метода
		return elements_.back().first;
	}
	Type& PeekMin() {
		// напишите реализацию метода
		return elements_.back().first;

	}
private:
	vector<pair<Type, Type>> elements_;
	// возможно, здесь вам понадобится что-то изменить
};

int main() {
	StackMin<int> stack;
	vector<int> values(5);

	// заполняем вектор для тестирования нашего стека
	iota(values.begin(), values.end(), 1);
	// перемешиваем значения
	random_shuffle(values.begin(), values.end());

	// заполняем стек
	for (int i = 0; i < 5; ++i) {
		stack.Push(values[i]);
	}

	// печатаем стек и его минимум, постепенно убирая из стека элементы
	while (!stack.IsEmpty()) {
		stack.Print();
		cout << "Минимум = " << stack.PeekMin() << endl;
		stack.Pop();
	}
}

*/
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
/*
using namespace std;
template<typename It>
void PrintRange(It tbegin, It tend) {

	for (auto t = tbegin; t != tend; t++) {
		cout << *t << " ";
	}
}

template <typename Type>
class Queue {
public:
	void Push(const Type& element) {
		// stack1 has FIFO, stack2 is reverse
		stack1_.push(element);

	}
	void Pop() {

		if (stack2_.empty()) {
			int st1 = stack1_.size();

			for (auto i = 0; i < st1; ++i) {
				stack2_.push(stack1_.top());
				stack1_.pop();
			}
		}
		stack2_.pop();
	}
	Type& Front() {
		  	if (stack2_.empty()) {
			int st1 = stack1_.size();

			for (auto i = 0; i < st1; ++i) {
				stack2_.push(stack1_.top());
				stack1_.pop();
			}
			}

			return stack2_.top();
		}
	const Type& Front() const {
		  	if (stack2_.empty()) {
			int st1 = stack1_.size();

			for (auto i = 0; i < st1; ++i) {
				stack2_.push(stack1_.top());
			}
		}

			return stack2_.top();
		};
	int Size() {

		return stack1_.size();
	}
	bool IsEmpty() const {

		return (stack1_.empty()&&stack2_.empty());
	}

private:
	stack<Type> stack1_;
	stack<Type> stack2_;
};

int main() {
	Queue<int> queue;
	vector<int> values(5);

	// заполняем вектор для тестирования очереди
	iota(values.begin(), values.end(), 1);
	// перемешиваем значения
	random_shuffle(values.begin(), values.end());

	PrintRange(values.begin(), values.end());

	cout << "Заполняем очередь" << endl;

	// заполняем очередь и выводим элемент в начале очереди
	for (int i = 0; i < 5; ++i) {
		queue.Push(values[i]);
		cout << "Вставленный элемент " << values[i] << endl;
		cout << "Первый элемент очереди " << queue.Front() << endl;
	}

	cout << "Вынимаем элементы из очереди" << endl;

	// выводим элемент в начале очереди и вытаскиваем элементы по одному
	while (!queue.IsEmpty()) {
		// сначала будем проверять начальный элемент, а потом вытаскивать,
		// так как операция Front на пустой очереди не определена
		cout << "Будем вынимать элемент " << queue.Front() << endl;
		queue.Pop();
	}
	return 0;
}


*/

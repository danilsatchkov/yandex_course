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
		// �������� ���������� ������
		if (elements_.empty())
		{
			elements_.push_back({ element, element });
			return;
		}
		elements_.push_back({ element,min(element,PeekMin()) });
	}
	void Pop() {
		// �������� ���������� ������
		elements_.pop_back();
	}
	const Type& Peek() const {
		return elements_.Peek();
	}
	Type& Peek() {
		return elements_.Peek();
	}
	void Print() const {
		// ������ ����� ������ �� ��������� �� �����,
		// �� ���� �� ��� �����, �� ������ ��� �����������
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
		// �������� ���������� ������
		return elements_.back().first;
	}
	Type& PeekMin() {
		// �������� ���������� ������
		return elements_.back().first;

	}
private:
	vector<pair<Type, Type>> elements_;
	// ��������, ����� ��� ����������� ���-�� ��������
};

int main() {
	StackMin<int> stack;
	vector<int> values(5);

	// ��������� ������ ��� ������������ ������ �����
	iota(values.begin(), values.end(), 1);
	// ������������ ��������
	random_shuffle(values.begin(), values.end());

	// ��������� ����
	for (int i = 0; i < 5; ++i) {
		stack.Push(values[i]);
	}

	// �������� ���� � ��� �������, ���������� ������ �� ����� ��������
	while (!stack.IsEmpty()) {
		stack.Print();
		cout << "������� = " << stack.PeekMin() << endl;
		stack.Pop();
	}
}

*/
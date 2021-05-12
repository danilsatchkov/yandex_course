#include <iostream>
#include <stdexcept>
#include <vector>
/*
using namespace std;

class Tower {
public:
	// ����������� � ����� SetDisks �����, ����� ��������� ������� �����
	Tower(int disks_num) {
		FillTower(disks_num);
	}

	int GetDisksNum() const {
		return disks_.size();
	}

	void SetDisks(int disks_num) {
		FillTower(disks_num);
	}

	// ��������� ���� �� ���� ����������� �����
	// �������� �������� �� ����������, ������� ������������� ���� �������
	void AddToTop(int disk) {
		int top_disk_num = disks_.size() - 1;
		if (0 != disks_.size() && disk >= disks_[top_disk_num]) {
			throw invalid_argument("���������� ��������� ������� ���� �� ���������");
		}
		else {
			// �������� ���� ����� � ����������� ��� � ����� �������
			disks_.push_back(disk);
		}
	}

	void RemoveFromTop() {
		
		disks_.pop_back();
		
	}

	// �� ������ ���������� ����������� ��� ������ ������� ������
	// disks_num - ���������� ������������ ������
// destination - �������� ����� ��� �����������
// buffer - �����, ������� ����� ������������ � �������� ������ ��� ������
	void MoveDisks(int disks_num, Tower& destination, Tower& buffer) {
		if (disks_num == 1) {
		
			RemoveFromTop();
			destination.AddToTop(1);
			return;	
		}
		
		//move n-1 from source to buffer , then move bottom from source to destination, then move n-1 from buffer to destination
			MoveDisks(disks_num - 1, buffer, destination);
			RemoveFromTop();
			destination.AddToTop(disks_num);
			buffer.MoveDisks(disks_num - 1, destination, *this);
		
	}

private:
	vector<int> disks_;

	// ���������� ��������� ����� FillTower, ����� �������� ���������� ����
	void FillTower(int disks_num) {
		for (int i = disks_num; i > 0; i--) {
			disks_.push_back(i);
		}
	}
};

 void SolveHanoi(vector<Tower>& towers) {
	 int disks_num = towers[0].GetDisksNum();
		 // ��������� ��������
		 // ������ ���������� ��� ����� �� ��������� �����
		 // � �������������� ������� ����� ��� ������
		 towers[0].MoveDisks(disks_num, towers[2], towers[1]);
		 cout << "test" << endl;
 }

int main() {
	int towers_num = 3;
	int disks_num = 6;
	vector<Tower> towers;
	// ������� � ������ ��� ������ �����
	for (int i = 0; i < towers_num; ++i) {
		towers.push_back(0);
	}
	// ������� �� ������ ����� ��� ������
	towers[0].SetDisks(disks_num);

	SolveHanoi(towers);

}

*/
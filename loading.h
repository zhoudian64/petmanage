#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
void out(void)
{
	int a, b, c, d;
	a = rand() % 6;
	b = rand() % 9;
	c = 0;
	d = rand() % 5;
	switch (a) {
	case 1:
		cout << "�ܵ���";
		break;
	case 2:
		cout << "���Ľ���";
		break;
	case 3:
		cout << "��������";
		break;
	case 4:
		cout << "������";
		break;
	case 5:
		cout << "����С�鶼��";
		break;
	case 0:
		b = -1;
		break;
	}
	switch (b) {
	case 0:
		cout << "��è";
		break;
	case 1:
		cout << "ߣ��";
		break;
	case 2:
		cout << "��BUG";
		break;
	case 3:
		cout << "�Ҷ���";
		break;
	case 4:
		cout << "ˢoj";
		break;
	case 5:
		cout << "��ʢ��";
		break;
	case 6:
		cout << "��ѼѼѧ��";
		break;
	case 7:
		cout << "�Է�";
		break;
	case 8:
		cout << "˯��";
		break;
	case -1:
		c = 1;
		break;
	}
	if (c == 1)
	{
		switch (d) {
		case 1:
			cout << "��Ҫ����petmanageҪ����������";
			break;
		case 2:
			cout << "��������͵���ء�";
			break;
		case 3:
			cout << "��ĵ������ò���Ŷ��";
			break;
		case 4:
			cout << "������������(=3=)";
			break;
		case 0:
			cout << "���ҿ���û�л������ѩn��";
			break;
		}
	}
	cout << endl;
}
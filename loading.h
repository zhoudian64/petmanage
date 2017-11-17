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
		cout << "周典在";
		break;
	case 2:
		cout << "管文杰在";
		break;
	case 3:
		cout << "宋哲宇在";
		break;
	case 4:
		cout << "蒋燕在";
		break;
	case 5:
		cout << "开发小组都在";
		break;
	case 0:
		b = -1;
		break;
	}
	switch (b) {
	case 0:
		cout << "吸猫";
		break;
	case 1:
		cout << "撸狗";
		break;
	case 2:
		cout << "修BUG";
		break;
	case 3:
		cout << "找对象";
		break;
	case 4:
		cout << "刷oj";
		break;
	case 5:
		cout << "打盛恺";
		break;
	case 6:
		cout << "奶鸭鸭学长";
		break;
	case 7:
		cout << "吃饭";
		break;
	case 8:
		cout << "睡觉";
		break;
	case -1:
		c = 1;
		break;
	}
	if (c == 1)
	{
		switch (d) {
		case 1:
			cout << "不要急，petmanage要坏掉了啦！";
			break;
		case 2:
			cout << "开发组在偷懒呢。";
			break;
		case 3:
			cout << "你的电脑配置不行哦。";
			break;
		case 4:
			cout << "卖个萌嘻嘻嘻(=3=)";
			break;
		case 0:
			cout << "找找看有没有坏东西⊙﹏⊙";
			break;
		}
	}
	cout << endl;
}
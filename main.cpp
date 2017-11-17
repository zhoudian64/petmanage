#include<fstream>
#include<cstring>
#include<string>
#include<iostream>
#include<conio.h>
#include"loading.h"
#include"GUI.h"
#include"PetList.h"
#include"MasterList.h"
using namespace std;
PetList PetStore;
MasterList Masters;
void CalculateCost()//计算主人花费和宠物数量 
{

	MasterListNode* p1;
	for (p1 = Masters.head.next; p1 != &Masters.tail; p1 = p1->next)
	{
		p1->petQuantity = 0;
		p1->allCost = 0;
		PetListNode* p2;
		for (p2 = PetStore.head.next; p2 != &PetStore.tail; p2 = p2->next)
		{
			if (p2->masterNumber == p1->masterNumber)
			{
				p1->petQuantity += 1;
				p1->allCost += (p2->price)*(p2->day);
			}
		}
	}
}
int main()
{
	system("title PetManage v1.1");
	system("mode con cols=65 lines=12");
	srand(time(0));
	load1();
	fstream musicconfig("config\\musicconfig.txt");
	string musicconfigtemp;
	musicconfig >> musicconfigtemp;
	if (musicconfigtemp == "y")
		bGM();
	musicconfig.close();
	fstream themeconfig("config\\themeconfig.txt");
	int themeconfigtemp;
	themeconfig >> themeconfigtemp;
	switch (themeconfigtemp)
	{
	case 1:system("color 0F"); break;
	case 2:system("color F0"); break;
	case 3:system("color 4F"); break;
	case 4:system("color 0A"); break;
	case 5:system("color 1F"); break;
	case 6:system("color 2F"); break;
	}
	themeconfig.close();
	system("cls");
	int flag = 0;//记录菜单
	char userin;
	bool bgmtimer = 0;
	//此处创建各变量
	load2();
	Masters.Input();
	//此处读取masterfile
	load3();
	PetStore.Input();
	//此处读取petfile
	load4();
	CalculateCost();
	//此处计算主人花费
mainMenu:	mainMenu();//主菜单 
	while (userin = _getche())
	{
		if (userin == '1')//宠物信息菜单 
			goto petMenu;
		if (userin == '2')//主人信息菜单 
			goto masterMenu;
		if (userin == 'm' || userin == 'M') //设置菜单
		{
			flag = 1;
			goto SettingMenu;
		}
		if (userin == 'q' || userin == 'Q') //退出
			return 0;
		error();
		goto mainMenu;
	}
petMenu: petMenu();//宠物信息菜单 
	while (userin = _getche())
	{
		if (userin == '1') //查询宠物信息 菜单 
			goto searchpetMenu;
		if (userin == '2') //删除宠物信息 菜单 
			goto deletepetMenu;
		if (userin == '3') //修改宠物信息 菜单 
			goto changepetMenu;
		if (userin == '4') //增加宠物信息
		{
			system("cls");
			cout << "请输入增加的宠物编号,返回请输入\\b后按回车键" << endl;
			string petnum;
			while (cin >> petnum)
			{
				if (petnum == "\\b")
					goto petMenu;
				else if (int N = atoi(petnum.c_str()))
				{
					if (PetStore.NumExist(N))
					{
						cout << "编号为" << N << "的宠物已经存在！" << endl;
						cout << "操作失败！" << endl;
					}
					else
					{
						cout << "请输入宠物名字，品种，主人编号，寄养天数和单日价格，以空格分开" << endl;
						string MasterNumberTemp = PetStore.AddInfo(N);
						if (Masters.NumExist(MasterNumberTemp))
						{
							cout << "该主人信息已存在，增加该宠物信息成功！" << endl;
							CalculateCost();
						}
						else
						{
							cout << "该主人信息不存在！请先录入改主人信息！" << endl;
							cout << "请输入该主人编号，名字和手机，以空格分开" << endl;
							Masters.AddInfo();
							cout << "增加主人信息成功！" << endl;
							cout << "增加宠物信息成功！" << endl;
							CalculateCost();
						}
					}
				}
				else
				{
					error();
					system("cls");
				}
				cout << "请输入增加的宠物编号,返回请输入\\b后按回车键" << endl;
			}
			//noExistError();
			//goto petMenu;
		}
		if (userin == 'm' || userin == 'M') //设置菜单
		{
			flag = 2;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B') //返回主菜单 
			goto mainMenu;
		error();
		goto petMenu;
	}
masterMenu: masterMenu();//主人信息菜单 
	while (userin = _getche())
	{
		if (userin == 'm' || userin == 'M') //设置菜单
		{
			flag = 3;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B') // 返回主菜单 
			goto mainMenu;
		if (userin == '1') //查看全部主人信息
		{
			Masters.PrintFiletemp();
			system("del temp\\temp2.txt");
			goto masterMenu;
		}
		if (userin == '2') //按照主人花费进行排序
		{
			Masters.MasterListSort();
			success();
			goto masterMenu;
		}
		error();
		goto masterMenu;
	}
searchpetMenu: SearchPetMenu();//查询宠物信息 菜单 
	while (userin = _getche())
	{
		if (userin == 'm' || userin == 'M') //设置菜单
		{
			flag = 4;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B') //返回 宠物信息菜单 
			goto petMenu;
		if (userin == '1') //根据编号查询宠物信息
		{
			system("cls");
			cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
			string petnum;
			while (cin >> petnum)
			{
				if (petnum == "\\b")
					goto searchpetMenu;
				else if (int N = atoi(petnum.c_str()))
				{
					cout << "编号为" << N << "的宠物的宠物信息:" << endl;
					string masternum = PetStore.SearchNum(N);
					if (masternum != "-1")
					{
						cout << "编号为" << N << "的宠物的主人信息:" << endl;
						Masters.SearchMasterNum(masternum);
					}
				}
				else
				{
					error();
					system("cls");
					//cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
				}
				cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
			}
		}
		if (userin == '2') //根据名字查询宠物信息
		{
			system("cls");
			cout << "请输入宠物名字,返回请输入\\b后按回车键" << endl;
			string n;
			while (cin >> n)
			{
				if (n == "\\b")
				{
					goto searchpetMenu;
				}
				else
				{
					cout << "名字为" << n << "的宠物的宠物信息:" << endl;
					string masternum = PetStore.SearchPetName(n);
					if (masternum != "-1")
					{
						cout << "名字为" << n << "的宠物的主人信息:" << endl;
						Masters.SearchMasterNum(masternum);
					}
				}
				cout << "请输入宠物名字,返回请输入\\b后按回车键" << endl;
			}
		}
		if (userin == '3') //查看全部宠物信息 
		{
			PetStore.PrintFiletemp();
			system("del temp\\temp.txt");
			goto searchpetMenu;
		}
		error();
		goto searchpetMenu;
	}
deletepetMenu:DeletePetMenu();//删除宠物信息 菜单 
	while (userin = _getche())
	{
		if (userin == 'm' || userin == 'M') //设置菜单
		{
			flag = 5;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B') // 返回 宠物信息菜单 
			goto petMenu;
		if (userin == '1') //根据编号删除宠物信息
		{
			system("cls");
			cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
			string n;
			while (cin >> n)
			{
				if (n == "\\b")
					goto deletepetMenu;
				cout << "是否确定要删除(Y/N）";
				string flag;
				cin >> flag;
				if (flag == "y" || flag == "Y")
					flag = "success";
				else if (flag == "n" || flag == "N")
				{
					cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
					continue;
				}
				else
				{
					error();
					system("cls");
				}
				if (int N = atoi(n.c_str()))
				{
					PetStore.Delete(N);
					CalculateCost();
					string MasterNumberTemp = Masters.IsPetQuantity();
					if (MasterNumberTemp != "-1")
					{
						Masters.Delete(MasterNumberTemp);
						cout << "编号为" << MasterNumberTemp << "的主人已没有宠物！" << endl;
						cout << "已删除编号为" << MasterNumberTemp << "的主人的信息！" << endl;
					}
				}

				else
				{
					error();
					system("cls");
				}
				cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
			}
			error();
			goto deletepetMenu;
		}
		if (userin == '2') //根据名字删除宠物信息
		{
			system("cls");
			cout << "请输入宠物名字,返回请输入\\b后按回车键" << endl;
			string n;
			while (cin >> n)
			{
				if (n == "\\b")
					goto deletepetMenu;
				cout << "是否确定要删除(Y/N）";
				string flag;
				cin >> flag;
				if (flag == "y" || flag == "Y")
					flag = "success";
				else if (flag == "n" || flag == "N")
				{
					cout << "请输入宠物名字,返回请输入\\b后按回车键" << endl;
					continue;
				}
				else
				{
					error();
					system("cls");
				}
				PetStore.NameDelete(n);
				CalculateCost();
				string MasterNumberTemp = Masters.IsPetQuantity();
				if (MasterNumberTemp != "-1")
				{
					Masters.Delete(MasterNumberTemp);
					cout << "编号为" << MasterNumberTemp << "的主人已没有宠物！" << endl;
					cout << "已删除编号为" << MasterNumberTemp << "的主人的信息！" << endl;
				}
				cout << "请输入宠物名字,返回请输入\\b后按回车键" << endl;
			}
		}
		error();
		goto deletepetMenu;
	}
changepetMenu:ChangePetMenu();//修改宠物信息 菜单 
	while (userin = _getche())
	{
		if (userin == 'm' || userin == 'M') //设置菜单
		{
			flag = 6;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B')//返回宠物信息菜单 
			goto petMenu;
		if (userin == '1') //根据宠物编号修改宠物寄养天数
		{
			system("cls");
			cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
			string petnum;
			while (cin >> petnum)
			{
				if (petnum == "\\b")
					goto changepetMenu;
				else if (int N = atoi(petnum.c_str()))
				{
					PetStore.ModifyPetDay(N);
					CalculateCost();
				}
				else
				{
					error();
					system("cls");
					//cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
				}
				cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
			}
		}
		if (userin == '2') //根据宠物编号修改宠物寄养价格
		{
			system("cls");
			cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
			string petnum;
			while (cin >> petnum)
			{
				if (petnum == "\\b")
					goto changepetMenu;
				else if (int N = atoi(petnum.c_str()))
				{
					PetStore.ModifyPetPrice(N);
					CalculateCost();
				}
				else
				{
					error();
					system("cls");
					//cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
				}
				cout << "请输入宠物编号,返回请输入\\b后按回车键" << endl;
			}
		}
		error();
		goto changepetMenu;
	}
SettingMenu: settingMenu();//设置 菜单
	while (userin = _getche())
	{
		if (userin == 'p' || userin == 'P') //音乐暂停和播放 
		{
			bgmtimer = MusicCountrl(bgmtimer);
			fstream musicconfig("config\\musicconfig.txt");
			if (bgmtimer == 1)
				musicconfig << "n";
			else
				musicconfig << "y";
			musicconfig.close();
			goto SettingMenu;
		}
		if (userin == 'a' || userin == 'A')//开发成员 
		{
			authorGUI();
			goto SettingMenu;
		}
		if (userin == 't' || userin == 'T')//主题设置
			goto SettingthemeMenu;
		if (userin == 's' || userin == 'S')//文件打印输出主人和宠物信息 
		{
			Masters.PrintFile();
			PetStore.PrintFile();
			success();
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B')//返回上层菜单
		{
			switch (flag)
			{
			case 1:goto mainMenu;
			case 2:goto petMenu;
			case 3:goto masterMenu;
			case 4:goto searchpetMenu;
			case 5:goto deletepetMenu;
			case 6:goto changepetMenu;
			}
		}
		error();
		goto SettingMenu;
	}
SettingthemeMenu: settingthemeMenu();//主题设置 菜单
	while (userin = _getche())
	{
		fstream themeconfig("config\\themeconfig.txt");
		switch (userin)
		{
		case '1':
		{
			system("color 0F");
			themeconfig << "1";
			break;
		}
		case '2':
		{
			system("color F0");
			themeconfig << "2";
			break;
		}
		case '3':
		{
			system("color 4F");
			themeconfig << "3";
			break;
		}
		case '4':
		{
			system("color 0A");
			themeconfig << "4";
			break;
		}
		case '5':
		{
			system("color 1F");
			themeconfig << "5";
			break;
		}
		case '6':
		{
			system("color 2F");
			themeconfig << "6";
			break;
		}
		case'b':goto SettingMenu;
		default: {
			error();
			goto SettingthemeMenu;
		}
		}
		goto SettingthemeMenu;
	}
}
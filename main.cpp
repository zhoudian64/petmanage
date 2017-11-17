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
void CalculateCost()//�������˻��Ѻͳ������� 
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
	int flag = 0;//��¼�˵�
	char userin;
	bool bgmtimer = 0;
	//�˴�����������
	load2();
	Masters.Input();
	//�˴���ȡmasterfile
	load3();
	PetStore.Input();
	//�˴���ȡpetfile
	load4();
	CalculateCost();
	//�˴��������˻���
mainMenu:	mainMenu();//���˵� 
	while (userin = _getche())
	{
		if (userin == '1')//������Ϣ�˵� 
			goto petMenu;
		if (userin == '2')//������Ϣ�˵� 
			goto masterMenu;
		if (userin == 'm' || userin == 'M') //���ò˵�
		{
			flag = 1;
			goto SettingMenu;
		}
		if (userin == 'q' || userin == 'Q') //�˳�
			return 0;
		error();
		goto mainMenu;
	}
petMenu: petMenu();//������Ϣ�˵� 
	while (userin = _getche())
	{
		if (userin == '1') //��ѯ������Ϣ �˵� 
			goto searchpetMenu;
		if (userin == '2') //ɾ��������Ϣ �˵� 
			goto deletepetMenu;
		if (userin == '3') //�޸ĳ�����Ϣ �˵� 
			goto changepetMenu;
		if (userin == '4') //���ӳ�����Ϣ
		{
			system("cls");
			cout << "���������ӵĳ�����,����������\\b�󰴻س���" << endl;
			string petnum;
			while (cin >> petnum)
			{
				if (petnum == "\\b")
					goto petMenu;
				else if (int N = atoi(petnum.c_str()))
				{
					if (PetStore.NumExist(N))
					{
						cout << "���Ϊ" << N << "�ĳ����Ѿ����ڣ�" << endl;
						cout << "����ʧ�ܣ�" << endl;
					}
					else
					{
						cout << "������������֣�Ʒ�֣����˱�ţ����������͵��ռ۸��Կո�ֿ�" << endl;
						string MasterNumberTemp = PetStore.AddInfo(N);
						if (Masters.NumExist(MasterNumberTemp))
						{
							cout << "��������Ϣ�Ѵ��ڣ����Ӹó�����Ϣ�ɹ���" << endl;
							CalculateCost();
						}
						else
						{
							cout << "��������Ϣ�����ڣ�����¼���������Ϣ��" << endl;
							cout << "����������˱�ţ����ֺ��ֻ����Կո�ֿ�" << endl;
							Masters.AddInfo();
							cout << "����������Ϣ�ɹ���" << endl;
							cout << "���ӳ�����Ϣ�ɹ���" << endl;
							CalculateCost();
						}
					}
				}
				else
				{
					error();
					system("cls");
				}
				cout << "���������ӵĳ�����,����������\\b�󰴻س���" << endl;
			}
			//noExistError();
			//goto petMenu;
		}
		if (userin == 'm' || userin == 'M') //���ò˵�
		{
			flag = 2;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B') //�������˵� 
			goto mainMenu;
		error();
		goto petMenu;
	}
masterMenu: masterMenu();//������Ϣ�˵� 
	while (userin = _getche())
	{
		if (userin == 'm' || userin == 'M') //���ò˵�
		{
			flag = 3;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B') // �������˵� 
			goto mainMenu;
		if (userin == '1') //�鿴ȫ��������Ϣ
		{
			Masters.PrintFiletemp();
			system("del temp\\temp2.txt");
			goto masterMenu;
		}
		if (userin == '2') //�������˻��ѽ�������
		{
			Masters.MasterListSort();
			success();
			goto masterMenu;
		}
		error();
		goto masterMenu;
	}
searchpetMenu: SearchPetMenu();//��ѯ������Ϣ �˵� 
	while (userin = _getche())
	{
		if (userin == 'm' || userin == 'M') //���ò˵�
		{
			flag = 4;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B') //���� ������Ϣ�˵� 
			goto petMenu;
		if (userin == '1') //���ݱ�Ų�ѯ������Ϣ
		{
			system("cls");
			cout << "�����������,����������\\b�󰴻س���" << endl;
			string petnum;
			while (cin >> petnum)
			{
				if (petnum == "\\b")
					goto searchpetMenu;
				else if (int N = atoi(petnum.c_str()))
				{
					cout << "���Ϊ" << N << "�ĳ���ĳ�����Ϣ:" << endl;
					string masternum = PetStore.SearchNum(N);
					if (masternum != "-1")
					{
						cout << "���Ϊ" << N << "�ĳ����������Ϣ:" << endl;
						Masters.SearchMasterNum(masternum);
					}
				}
				else
				{
					error();
					system("cls");
					//cout << "�����������,����������\\b�󰴻س���" << endl;
				}
				cout << "�����������,����������\\b�󰴻س���" << endl;
			}
		}
		if (userin == '2') //�������ֲ�ѯ������Ϣ
		{
			system("cls");
			cout << "�������������,����������\\b�󰴻س���" << endl;
			string n;
			while (cin >> n)
			{
				if (n == "\\b")
				{
					goto searchpetMenu;
				}
				else
				{
					cout << "����Ϊ" << n << "�ĳ���ĳ�����Ϣ:" << endl;
					string masternum = PetStore.SearchPetName(n);
					if (masternum != "-1")
					{
						cout << "����Ϊ" << n << "�ĳ����������Ϣ:" << endl;
						Masters.SearchMasterNum(masternum);
					}
				}
				cout << "�������������,����������\\b�󰴻س���" << endl;
			}
		}
		if (userin == '3') //�鿴ȫ��������Ϣ 
		{
			PetStore.PrintFiletemp();
			system("del temp\\temp.txt");
			goto searchpetMenu;
		}
		error();
		goto searchpetMenu;
	}
deletepetMenu:DeletePetMenu();//ɾ��������Ϣ �˵� 
	while (userin = _getche())
	{
		if (userin == 'm' || userin == 'M') //���ò˵�
		{
			flag = 5;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B') // ���� ������Ϣ�˵� 
			goto petMenu;
		if (userin == '1') //���ݱ��ɾ��������Ϣ
		{
			system("cls");
			cout << "�����������,����������\\b�󰴻س���" << endl;
			string n;
			while (cin >> n)
			{
				if (n == "\\b")
					goto deletepetMenu;
				cout << "�Ƿ�ȷ��Ҫɾ��(Y/N��";
				string flag;
				cin >> flag;
				if (flag == "y" || flag == "Y")
					flag = "success";
				else if (flag == "n" || flag == "N")
				{
					cout << "�����������,����������\\b�󰴻س���" << endl;
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
						cout << "���Ϊ" << MasterNumberTemp << "��������û�г��" << endl;
						cout << "��ɾ�����Ϊ" << MasterNumberTemp << "�����˵���Ϣ��" << endl;
					}
				}

				else
				{
					error();
					system("cls");
				}
				cout << "�����������,����������\\b�󰴻س���" << endl;
			}
			error();
			goto deletepetMenu;
		}
		if (userin == '2') //��������ɾ��������Ϣ
		{
			system("cls");
			cout << "�������������,����������\\b�󰴻س���" << endl;
			string n;
			while (cin >> n)
			{
				if (n == "\\b")
					goto deletepetMenu;
				cout << "�Ƿ�ȷ��Ҫɾ��(Y/N��";
				string flag;
				cin >> flag;
				if (flag == "y" || flag == "Y")
					flag = "success";
				else if (flag == "n" || flag == "N")
				{
					cout << "�������������,����������\\b�󰴻س���" << endl;
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
					cout << "���Ϊ" << MasterNumberTemp << "��������û�г��" << endl;
					cout << "��ɾ�����Ϊ" << MasterNumberTemp << "�����˵���Ϣ��" << endl;
				}
				cout << "�������������,����������\\b�󰴻س���" << endl;
			}
		}
		error();
		goto deletepetMenu;
	}
changepetMenu:ChangePetMenu();//�޸ĳ�����Ϣ �˵� 
	while (userin = _getche())
	{
		if (userin == 'm' || userin == 'M') //���ò˵�
		{
			flag = 6;
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B')//���س�����Ϣ�˵� 
			goto petMenu;
		if (userin == '1') //���ݳ������޸ĳ����������
		{
			system("cls");
			cout << "�����������,����������\\b�󰴻س���" << endl;
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
					//cout << "�����������,����������\\b�󰴻س���" << endl;
				}
				cout << "�����������,����������\\b�󰴻س���" << endl;
			}
		}
		if (userin == '2') //���ݳ������޸ĳ�������۸�
		{
			system("cls");
			cout << "�����������,����������\\b�󰴻س���" << endl;
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
					//cout << "�����������,����������\\b�󰴻س���" << endl;
				}
				cout << "�����������,����������\\b�󰴻س���" << endl;
			}
		}
		error();
		goto changepetMenu;
	}
SettingMenu: settingMenu();//���� �˵�
	while (userin = _getche())
	{
		if (userin == 'p' || userin == 'P') //������ͣ�Ͳ��� 
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
		if (userin == 'a' || userin == 'A')//������Ա 
		{
			authorGUI();
			goto SettingMenu;
		}
		if (userin == 't' || userin == 'T')//��������
			goto SettingthemeMenu;
		if (userin == 's' || userin == 'S')//�ļ���ӡ������˺ͳ�����Ϣ 
		{
			Masters.PrintFile();
			PetStore.PrintFile();
			success();
			goto SettingMenu;
		}
		if (userin == 'b' || userin == 'B')//�����ϲ�˵�
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
SettingthemeMenu: settingthemeMenu();//�������� �˵�
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
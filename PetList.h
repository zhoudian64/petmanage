#ifndef PETLIST_H
#define PETLIST_H
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define INF 0x3f3f3f
fstream file("temp\\PetList_100.txt");
class PetListNode
{
public:
	int petNumber;
	string petName;
	string petBreed;
	string masterNumber;
	int day;
	int price;
	PetListNode* next;
	PetListNode* previous;
	PetListNode()
	{
		next = NULL;
		previous = NULL;
	}
	~PetListNode() {}
};

class PetList
{
private:

	void Input(PetListNode*&);
	void Delete(PetListNode*&, int);
	void NameDelete(PetListNode*&, string);
	void ModifyPetPrice(PetListNode*&, int);
	void ModifyPetDay(PetListNode*&, int);
	string AddInfo(PetListNode*&, int);
	string SearchNum(PetListNode*, int);
	string SearchPetName(PetListNode*, string);
	void CreateBackPointer(PetListNode*&);
	void CreateFirstBackPointer(PetListNode*&);
	bool NumExist(PetListNode*, int);
public:
	PetListNode head, tail;
	void PrintFile();                 //�������г�����Ϣ�����ļ����
	void PrintFiletemp();             //��ʱ��ӡ�Բ�ѯȫ��������Ϣ
	void Input();                     //�����ʼ�ļ���ʹ���ļ�����        
	void Delete(int);                 //ɾ�����Ϊ(int)�ĳ���
	void NameDelete(string);          //ɾ������Ϊ(string)�ĳ���
	void ModifyPetPrice(int);         //�޸ı��Ϊ(int)�ĳ���۸�               
	void ModifyPetDay(int);           //�޸ı��Ϊ(int)�ĳ�������              
	string AddInfo(int);              //��ӱ��Ϊ(int)�ĳ���������˱��                                 
	string SearchNum(int);            //���ұ��Ϊ(int)�ĳ���������˱��               
	string SearchPetName(string);	  //��������Ϊ(string)�ĳ���������˱��                                                   
	bool NumExist(int);               //�����Ϊ(int)�ĳ����Ƿ����             
	PetList()
	{
		head.masterNumber = "head";
		tail.masterNumber = "tail";
		head.next = &tail;
		tail.previous = &head;
		head.previous = NULL;
		tail.next = NULL;
		head.petNumber = INF;
		tail.petNumber = -1;
	}

	~PetList() {}
};

void PetList::PrintFile()
{
	ofstream fileout("PetListOutput.txt");
	PetListNode* Temp;
	for (Temp = head.next; Temp != &tail; Temp = Temp->next)
	{
		fileout << Temp->petNumber;
		fileout << " " << Temp->petName;
		fileout << " " << Temp->petBreed;
		fileout << " " << Temp->masterNumber;
		fileout << " " << Temp->day;
		fileout << " " << Temp->price << endl;
	}
	fileout.close();
}

void PetList::PrintFiletemp()
{
	system("cls");
	ofstream fileouttemp("temp\\temp.txt");
	PetListNode* Temp;
	for (Temp = head.next; Temp != &tail; Temp = Temp->next)
	{
		fileouttemp << Temp->petNumber;
		fileouttemp << " " << Temp->petName;
		fileouttemp << " " << Temp->petBreed;
		fileouttemp << " " << Temp->masterNumber;
		fileouttemp << " " << Temp->day;
		fileouttemp << " " << Temp->price << endl;
	}
	fileouttemp.close();
	system("temp\\temp.txt");
}

void PetList::Input(PetListNode* &Temp)
{
	int Num, Day, Price;
	string Name, Breed, mNum;
	file >> Num;
	if (Num == -1)
	{
		Temp = &tail;
		CreateFirstBackPointer(head.next);
		CreateBackPointer(head.next);
		return;
	}
	else
	{
		file >> Name >> Breed >> mNum >> Day >> Price;
		Temp = new PetListNode;
		Temp->petNumber = Num;
		Temp->petName = Name;
		Temp->petBreed = Breed;
		Temp->masterNumber = mNum;
		Temp->day = Day;
		Temp->price = Price;
		Input(Temp->next);
	}
}

void PetList::Input()
{
	head.next = new PetListNode;
	Input(head.next);
}

void PetList::CreateFirstBackPointer(PetListNode* &Temp)
{
	Temp->previous = &head;
}

void PetList::CreateBackPointer(PetListNode* &Temp)
{
	Temp->next->previous = Temp;
	if (Temp->next != &tail)
	{
		CreateBackPointer(Temp->next);
	}
}

void PetList::Delete(PetListNode* &Temp, int Num)
{
	if (Temp == &tail)
	{
		cout << "�˳��ﲻ���ڣ�" << endl;
		return;
	}
	if (Temp->petNumber == Num)
	{
		Temp->next->previous = Temp->previous;
		Temp->previous->next = Temp->next;
		cout << "ɾ���ɹ���" << endl;
	}
	else
	{
		Delete(Temp->next, Num);
	}
}

void PetList::Delete(int Num)
{
	Delete(head.next, Num);
}

void PetList::NameDelete(PetListNode* &Temp, string Name)
{
	if (Temp == &tail)
	{
		cout << "�˳��ﲻ���ڣ�" << endl;
		return;
	}
	if (Temp->petName == Name)
	{
		Temp->next->previous = Temp->previous;
		Temp->previous->next = Temp->next;
		cout << "ɾ���ɹ���" << endl;
	}
	else
	{
		NameDelete(Temp->next, Name);
	}
}

void PetList::NameDelete(string Name)
{
	NameDelete(head.next, Name);
}

string PetList::SearchNum(PetListNode* Temp, int Num)
{
	if (Temp == &tail)
	{
		string Tempstr = "-1";
		cout << "�˳��ﲻ���ڣ�" << endl;
		return Tempstr;
	}
	if (Temp->petNumber == Num)
	{
		cout << Temp->petNumber;
		cout << " " << Temp->petName;
		cout << " " << Temp->petBreed;
		cout << " " << Temp->masterNumber << endl;
		return Temp->masterNumber;
	}
	else
	{
		return SearchNum(Temp->next, Num);
	}
}

string PetList::SearchNum(int Num)
{
	return SearchNum(head.next, Num);
}

string PetList::SearchPetName(PetListNode* Temp, string Name)
{
	if (Temp == &tail)
	{
		string Tempstr = "-1";
		cout << "�˳��ﲻ����" << endl;
		return Tempstr;
	}
	if (Temp->petName == Name)
	{
		cout << Temp->petNumber;
		cout << " " << Temp->petName;
		cout << " " << Temp->petBreed;
		cout << " " << Temp->masterNumber << endl;
		return Temp->masterNumber;
	}
	else
	{
		return SearchPetName(Temp->next, Name);
	}
}

string PetList::SearchPetName(string Name)
{
	return SearchPetName(head.next, Name);
}

void PetList::ModifyPetPrice(PetListNode* &Temp, int Num)
{
	if (Temp == &tail)
	{
		cout << "�˳��ﲻ���ڣ�" << endl;
		return;
	}
	if (Temp->petNumber == Num)
	{
		cout << "�������µļ۸�" << endl;
		cin >> Temp->price;
		cout << "�޸ĳɹ���" << endl;
	}
	else
	{
		ModifyPetPrice(Temp->next, Num);
	}
}

void PetList::ModifyPetPrice(int Num)
{
	ModifyPetPrice(head.next, Num);
}

void PetList::ModifyPetDay(PetListNode* &Temp, int Num)
{
	if (Temp == &tail)
	{
		cout << "�˳��ﲻ���ڣ�" << endl;
		return;
	}
	if (Temp->petNumber == Num)
	{
		cout << "�������µļ���������" << endl;
		cin >> Temp->day;
		cout << "�޸ĳɹ���" << endl;
	}
	else
	{
		ModifyPetDay(Temp->next, Num);
	}
}

void PetList::ModifyPetDay(int Num)
{
	ModifyPetDay(head.next, Num);
}

string PetList::AddInfo(PetListNode* &Temp, int Num)
{
	if (Temp->next == &tail)
	{
		Temp->next = new PetListNode;
		Temp->next->next = &tail;
		tail.previous = Temp->next;
		Temp->next->previous = Temp;
		//cout<<"Input the Information of the New Pet:"<<endl;
		Temp->next->petNumber = Num;
		cin >> Temp->next->petName;
		cin >> Temp->next->petBreed;
		cin >> Temp->next->masterNumber;
		cin >> Temp->next->day;
		cin >> Temp->next->price;
		return Temp->next->masterNumber;
	}
	else
	{
		return AddInfo(Temp->next, Num);
	}
}

string PetList::AddInfo(int Num)
{
	return AddInfo(head.next, Num);
}

bool PetList::NumExist(PetListNode* Temp, int Num)
{
	if (Temp == &tail)
	{
		return false;
	}
	if (Temp->petNumber == Num)
	{
		return true;
	}
	else
	{
		return NumExist(Temp->next, Num);
	}
}

bool PetList::NumExist(int Num)
{
	return NumExist(head.next, Num);
}

#endif

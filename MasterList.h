#ifndef MASTERLIST_H
#define MASTERLIST_H

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define INF 0x3f3f3f

fstream filetwo("temp\\MasterList.txt");

class MasterListNode
{
public:
	string masterNumber;
	string masterName;
	string contactMethod;
	int petQuantity;
	int allCost;
	MasterListNode* next;
	MasterListNode* previous;

	MasterListNode()
	{
		next = NULL;
		previous = NULL;
		masterNumber = "Unknown";
		masterName = "";
		contactMethod = "";
		petQuantity = 0;
		allCost = 0;
	}

	~MasterListNode() {}
};

class MasterList
{
private:
	void Input(MasterListNode*&);
	void Delete(MasterListNode*&, string);
	void Move(MasterListNode*&, MasterListNode*&, string, string);
	void AddInfo(MasterListNode*&);
	void SearchMasterName(MasterListNode*, string);
	void SearchMasterNum(MasterListNode*, string);
	void MasterListSort(MasterListNode*&, MasterListNode*&);
	void CreateBackPointer(MasterListNode*&);
	void CreateFirstBackPointer(MasterListNode*&);
	bool NumExist(MasterListNode*, string);
public:
	MasterListNode head, tail;
	void Input();                           //�����ʼ�ļ���ʹ���ļ�����        
	void Delete(string);                    //ɾ�����Ϊ(string)������                              
	void Move(string, string);               //�ƶ����Ϊ(string)�����������Ϊ(string)������֮���������˻�������                        
	void AddInfo();                         //��ӱ��Ϊ(string)������       
	void SearchMasterName(string);          //���ұ��Ϊ(string)������       
	void SearchMasterNum(string);           //��������Ϊ(string)������        
	void MasterListSort();                  //�������˵Ļ��ѽ�������                                         
	void PrintFile();                       //��������������Ϣ�����ļ����
	void PrintFiletemp();                   //��ʱ��ӡ�Բ�ѯȫ��������Ϣ              
	bool NumExist(string);                  //�����Ϊ(string)�������Ƿ����        
	string IsPetQuantity();                 //�ж����������Ƿ�������һ���������-1���޳�������˱�� 

	MasterList()
	{
		head.masterNumber = "head";
		tail.masterNumber = "tail";
		head.next = &tail;
		tail.previous = &head;
		head.previous = NULL;
		tail.next = NULL;
		head.allCost = INF;
		tail.allCost = -1;
	}

	~MasterList() {}
};

void MasterList::Input(MasterListNode* &Temp)
{
	string Num, Name, Tel;
	int Quantity, Cost = 0;
	filetwo >> Num;
	if (Num == "-1")
	{
		Temp = &tail;
		CreateFirstBackPointer(head.next);
		CreateBackPointer(head.next);
		return;
	}
	else
	{
		filetwo >> Name >> Tel >> Quantity;// >> Cost;
		Temp = new MasterListNode;
		Temp->masterNumber = Num;
		Temp->masterName = Name;
		Temp->contactMethod = Tel;
		Temp->petQuantity = Quantity;
		Temp->allCost = Cost;
		Input(Temp->next);
	}
}

void MasterList::Input()
{
	head.next = new MasterListNode;
	Input(head.next);
}

void MasterList::CreateFirstBackPointer(MasterListNode* &Temp)
{
	Temp->previous = &head;
}

void MasterList::CreateBackPointer(MasterListNode* &Temp)
{
	Temp->next->previous = Temp;
	if (Temp->next != &tail)
	{
		CreateBackPointer(Temp->next);
	}
}

void MasterList::PrintFile()
{
	ofstream fileouttwo("MasterListOutput.txt");
	MasterListNode* Temp;
	for (Temp = head.next; Temp != &tail; Temp = Temp->next)
	{
		fileouttwo << Temp->masterNumber;
		fileouttwo << " " << Temp->masterName;
		fileouttwo << " " << Temp->contactMethod;
		fileouttwo << " " << Temp->petQuantity;
		fileouttwo << " " << Temp->allCost << endl;
	}
	fileouttwo.close();
}

void MasterList::PrintFiletemp()
{
	system("cls");
	ofstream fileouttwotemp("temp\\temp2.txt");
	MasterListNode* Temp;
	for (Temp = head.next; Temp != &tail; Temp = Temp->next)
	{
		fileouttwotemp << Temp->masterNumber;
		fileouttwotemp << " " << Temp->masterName;
		fileouttwotemp << " " << Temp->contactMethod;
		fileouttwotemp << " " << Temp->petQuantity;
		fileouttwotemp << " " << Temp->allCost << endl;
	}
	fileouttwotemp.close();
	system("temp\\temp2.txt");
}

void MasterList::Delete(MasterListNode* &Temp, string Num)
{
	if (Temp == &tail)
	{
		cout << "No Such Information" << endl;
		return;
	}
	if (Temp->masterNumber == Num)
	{
		Temp->next->previous = Temp->previous;
		Temp->previous->next = Temp->next;
	}
	else
	{
		Delete(Temp->next, Num);
	}
}

void MasterList::Delete(string Num)
{
	Delete(head.next, Num);
}

void MasterList::SearchMasterNum(MasterListNode* Temp, string Num)
{
	if (Temp == &tail)
	{
		cout << "No Such Information" << endl;
		return;
	}
	if (Temp->masterNumber == Num)
	{
		cout << Temp->masterNumber;
		cout << " " << Temp->masterName;
		cout << " " << Temp->contactMethod << endl;
	}
	else
	{
		SearchMasterNum(Temp->next, Num);
	}
}

void MasterList::SearchMasterNum(string Num)
{
	SearchMasterNum(head.next, Num);
}

void MasterList::SearchMasterName(MasterListNode* Temp, string Name)
{
	if (Temp == &tail)
	{
		cout << "No Such Information" << endl;
		return;
	}
	if (Temp->masterName == Name)
	{
		cout << Temp->masterNumber;
		cout << " " << Temp->masterName;
		cout << " " << Temp->contactMethod << endl;
	}
	else
	{
		SearchMasterName(Temp->next, Name);
	}
}

void MasterList::SearchMasterName(string Name)
{
	SearchMasterName(head.next, Name);
}

void MasterList::AddInfo(MasterListNode* &Temp)
{
	if (Temp->next == &tail)
	{
		Temp->next = new MasterListNode;
		Temp->next->next = &tail;
		tail.previous = Temp->next;
		Temp->next->previous = Temp;
		//cout<<"Input the Information of the New Master:"<<endl;
		cin >> Temp->next->masterNumber;
		cin >> Temp->next->masterName;
		cin >> Temp->next->contactMethod;
		//cin>>Temp->next->petQuantity;
	}
	else
	{
		AddInfo(Temp->next);
	}
}

void MasterList::AddInfo()
{
	AddInfo(head.next);
}

void MasterList::Move(MasterListNode* &Temp1, MasterListNode* &Temp2, string start, string destiny)
{
	if (Temp1 == &tail || Temp2 == &tail)
	{
		cout << "No Such Information" << endl;
		return;
	}
	if (Temp1->masterNumber != start)
	{
		Move(Temp1->next, Temp2, start, destiny);
	}
	else if (Temp2->masterNumber != destiny)
	{
		Move(Temp1, Temp2->next, start, destiny);
	}
	else
	{
		MasterListNode* TempNode = new MasterListNode;
		TempNode->masterNumber = Temp2->masterNumber;
		TempNode->masterName = Temp2->masterName;
		TempNode->contactMethod = Temp2->contactMethod;
		TempNode->petQuantity = Temp2->petQuantity;
		TempNode->allCost = Temp2->allCost;
		TempNode->next = Temp1->next;
		TempNode->previous = Temp1;
		Temp1->next->previous = TempNode;
		Temp1->next = TempNode;
		Temp2->next->previous = Temp2->previous;
		Temp2->previous->next = Temp2->next;
	}
}

void MasterList::Move(string start, string destiny)
{
	Move(head.next, head.next, start, destiny);
}

void MasterList::MasterListSort(MasterListNode* &Temp1, MasterListNode* &Temp2)
{
	if (Temp1 == &head)
	{
		cout << "Sort Completed!" << endl;
		return;
	}
	if ((Temp2 != &tail) && (Temp2->allCost >= Temp1->allCost))
	{
		MasterListSort(Temp1, Temp2->next);
	}
	else
	{
		MasterListNode* TempNode = Temp1->previous;
		Move(Temp2->previous->masterNumber, Temp1->masterNumber);
		MasterListSort(TempNode, TempNode);
	}
}

void MasterList::MasterListSort()
{
	MasterListSort(tail.previous, tail.previous);
}

bool MasterList::NumExist(MasterListNode* Temp, string Num)
{
	if (Temp == &tail)
	{
		return false;
	}
	if (Temp->masterNumber == Num)
	{
		return true;
	}
	else
	{
		return NumExist(Temp->next, Num);
	}
}

bool MasterList::NumExist(string Num)
{
	return NumExist(head.next, Num);
}

string MasterList::IsPetQuantity()
{
	MasterListNode* Temp;
	for (Temp = head.next; Temp != &tail; Temp = Temp->next)
	{
		if (Temp->petQuantity == 0)
			return Temp->masterNumber;
	}
	return "-1";
}


#endif

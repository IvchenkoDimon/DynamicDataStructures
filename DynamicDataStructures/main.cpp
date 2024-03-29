#include <iostream>

using namespace std;

#define tab "\t"
#define delimeter "\n---------------------------------------------------------\n"
//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define INDEX_OPERATOR_CHECK
//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
	int size;
public:
	const int get_size() const
	{
		return this->size;
	}
	ForwardList()
	{
		this->Head = nullptr;
		this->size = 0;
		//���������� ������� ������ ������.
#ifdef DEBUG
		cout << "FLConstructor:\t" << this << endl;
#endif // DEBUG
	}

	ForwardList(int size) :ForwardList()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		while (size--)push_front(int());
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		//cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			//it - ��������;
			//begin - ���������� ����� ������ ���������� il;
			//end - ���������� ����� ����� ���������� il;
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "FLDestructor:\t" << this << endl;
	}
	//			Operators:
	int& operator[](int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	//			Adding Elements:
	void push_front(int Data)
	{
		////��������� �������� � ������ ������.
		////1) ������� �������, � ������� ����� �������� ����������� ��������.
		//Element* New = new Element(Data);
		////2) �������������� ����� ������� � ������ ������:
		//New->pNext = Head;
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		size++;
	}
	//			deleting elements:
	void pop_front()
	{
		Element* Temp = Head;//���������� ����� ���������� ��������.
		Head = Head->pNext; //��������� ������� �� ������.
		delete Temp; //������� ������� �� ������.
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)
		{
			pop_front();
			return;
		}
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index >= Element::count)
		{
			//pop_back();
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		Element* toDel = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete toDel;
		size--;
	}

	void print()
	{
		//Element* Temp = Head; //Temp - ��� ��������.
		//�������� ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������.
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;//��������� �� ��������� �������.
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "���������� ��������� ������: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n; //���������� ��������� ������.
	cout << "������� �������� ���������: "; cin >> n;
#ifdef BASE_CHECK
	ForwardList fl; //������� ������ ������.
	for (int i = 0; i < n; i++)
	{
		fl.push_back(rand() % 100);
	}
	fl.push_back(123);
	fl.print();
	cout << delimeter << endl;
	fl.pop_front();
	fl.print();
	cout << delimeter << endl;
	fl.pop_back();
	fl.print();
	cout << delimeter << endl;
	int Index;
	int Data;
	cout << "������� ������ ������������ ��������: "; cin >> Index;
	cout << "������� �������� ������������ ��������: "; cin >> Data;
	fl.insert(Index, Data);
	fl.print();
	cout << delimeter << endl;
	cout << "������� ������ ���������� ��������: "; cin >> Index;
	fl.erase(Index);
	fl.print();
#endif // BASE_CHECK
#ifdef DESTRUCTOR_CHECK
	ForwardList chain;
	for (int i = 0; i < n; i++)
	{
		chain.push_front(rand() % 100);
	}
	//chain.print();
	cout << "List full" << endl;
#endif // DESTRUCTOR_CHECK
#ifdef INDEX_OPERATOR_CHECK
	ForwardList fl(n);
	fl.print();
	for (int i = 0; i < fl.get_size(); i++)
	{
		fl[i] = rand() % 100;
	}
	for (int i = 0; i < fl.get_size(); i++)
	{
		cout << fl[i] << tab;
	}
	cout << endl;
#endif // INDEX_OPERATOR_CHECK
#ifdef CONSTRUCTORS_CHECK
	
	ForwardList fl1 = { 3, 5 , 8 , 13 ,21 };
	for (int i = 0; i < fl1.get_size(); i++)
		cout << fl1[i] << tab;
	cout << endl;
	ForwardList fl2 = fl1; //CopyConstructor
	fl2.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	
	ForwardList fl1 = { 3,5,8,13,21 };
	ForwardList fl2 = { 34,55,89 };
	for (int i = 0; i < fl1.get_size(); i++)
	{
		cout << fl1[i] << tab;
	}
	cout << endl;
	for (int i = 0; i < fl2.get_size(); i++)
	{
		cout << fl2[i] << tab;
	}
	cout << endl;
	ForwardList fl3;
	fl3 = fl1 + fl2;
	fl3.print();
#endif // OPERATORS_CHECK
}
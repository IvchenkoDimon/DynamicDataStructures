#include <iostream>

using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		this->Head = nullptr;
		//Изначально создаем пустой список.
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
	}
	//			Adding Elements:
	void push_front(int Data)
	{
		//добавляет значение в начало списка.
		//1) Создаем элемент, в который будет помещено добавляемое значение.
		Element* New = new Element(Data);
		//2) Пристыковываем новый элемент к началу списка:
		New->pNext = Head;
		Head = New;
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
	}
	void print()
	{
		Element* Temp = Head; //Temp - это итератор.
		//Итератор это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//Переходим на следующий элемент.
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n; //количество элементов списка.
	cout << "Введите колиство элементов: "; cin >> n;
	ForwardList fl; //создаем пустой список.
	for (int i = 0; i < n; i++)
	{
		fl.push_back(rand() % 100);
	}
	fl.push_back(123);
	fl.print();
}
#include <iostream>

using namespace std;

#define tab "\t"
#define delimeter "\n---------------------------------------------------------\n"
//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
#define INDEX_OPERATOR_CHECK

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
	ForwardList()
	{
		this->Head = nullptr;
		this->size = 0;
		//Изначально создаем пустой список.
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
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "FLDestructor:\t" << this << endl;
	}
	//			Adding Elements:
	void push_front(int Data)
	{
		////добавляет значение в начало списка.
		////1) Создаем элемент, в который будет помещено добавляемое значение.
		//Element* New = new Element(Data);
		////2) Пристыковываем новый элемент к началу списка:
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
		Element* Temp = Head;//запоминаем адрес удаляемого элемента.
		Head = Head->pNext; //исключаем элемент из списка.
		delete Temp; //удаляем элемент из памяти.
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
		//Element* Temp = Head; //Temp - это итератор.
		//Итератор это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;//Переходим на следующий элемент.
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n; //количество элементов списка.
	cout << "Введите колиство элементов: "; cin >> n;
#ifdef BASE_CHECK
	ForwardList fl; //создаем пустой список.
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
	cout << "Введите инлекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> Data;
	fl.insert(Index, Data);
	fl.print();
	cout << delimeter << endl;
	cout << "Введите инлекс удаляемого элемента: "; cin >> Index;
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
	/*for (int i = 0; i < fl.get_size(); i++)
	{
		cout << fl[i] << "\t";
	}
	cout << endl;*/
#endif // INDEX_OPERATOR_CHECK

}
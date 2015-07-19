#include <iostream>
using namespace std;
 

struct Element
{
   // Данные
   char data;
   // Адрес следующего элемента списка
   Element * Next;
};

// Односвязный список
class List
{
   // Адрес головного элемента списка
   Element * Head;
   // Адрес головного элемента списка
   Element * Tail;
   // Количество элементов списка
   int Count;

public:
   // Конструктор
   List();
   // Деструктор
   ~List();
	
   // Добавление элемента в список
   // (Новый элемент становится последним)
   void Add(char data);
	
   // Удаление элемента списка
   // (Удаляется головной элемент)
   void Del();
   // Удаление всего списка
   void DelAll();
	
   // Распечатка содержимого списка
   // (Распечатка начинается с головного элемента)
   void Print();
	
   // Получение количества элементов, находящихся в списке
   int GetCount();

   // Всатвка элемента в заданную позицию
   void Insert(char data, int pos);

   //удаление элемента из заданной позиции
   char Delete(int pos);

   //поиск заданного элемента
   int Search(char data);
};

List::List()
{
   // Изначально список пуст
   Head = Tail = NULL;   
   Count = 0;
}

List::~List()
{
   // Вызов функции удаления
   DelAll();
}

int List::GetCount()
{
   // Возвращаем количество элементов
   return Count;
}

void List::Add(char data)
{
   // создание нового элемента
   Element * temp = new Element;

   // заполнение данными
   temp->data = data;
   // следующий элемент отсутствует
   temp->Next = NULL;
   // новый элемент становится последним элементом списка
   // если он не первый добавленный
   if(Head!=NULL){
		Tail->Next=temp;
		Tail = temp;
		++Count;
   }
   // новый элемент становится единственным
   // если он первый добавленный
   else{
	   Head=Tail=temp;
	   ++Count;
   }
}

void List::Del()
{
   // запоминаем адрес головного элемента
   Element * temp = Head;
   // перебрасываем голову на следующий элемент
   Head = Head->Next;
   // удаляем бывший головной элемент
   delete temp;
}

void List::DelAll()
{
   // Пока еще есть элементы
   while(Head != 0)
      // Удаляем элементы по одному
      Del();
}

void List::Print()
{
   // запоминаем адрес головного элемента
   Element * temp = Head;
   // Пока еще есть элементы
   while(temp != 0)
   {
      // Выводим данные
      cout << temp->data << " ";
      // Переходим на следующий элемент
      temp = temp->Next;
   }

   cout << "\n\n";
}

void List::Insert(char data, int pos) {
	if(pos<Count+1) {
		int i;
		Element* temp_head = Head;
		for(i = 0;i<pos;++i) {//1 2 3 
			temp_head = temp_head->Next;
		}
		//теперь temp_head указывает на эелемент после которого встанет новый элемент
		if(i == 0) {
			Element* temp = new Element;
			temp->data = data;
			temp->Next = Head;
			Head = temp;
		}
		else if(i == Count - 1) {
			Element* temp = new Element;
			temp->Next = temp_head->Next;
			temp->data = data;
			Tail = temp;
			temp_head->Next = temp;
		}
		else {
			Element* temp = new Element;
			temp->data = temp_head->data;
			temp->Next = temp_head->Next;
			temp_head->data = data;
			temp_head->Next = temp;

		}

		//Если добавляем в конец, то надо поменять хвост
		

		//увеличиваем количество
		++Count;
	}

}

int List::Search(char data) {
	Element* temp_head = Head;
	int pos = 0;
	while(temp_head) {
		if(temp_head->data == data)
			return pos;
		else {
			++pos;
			temp_head = temp_head->Next;
		}
	}
	return NULL;
}

char List::Delete(int pos) {
	Element* temp_head = Head;
	
	if(pos>=Count || Count == 0)
		return '\0';

	//перемещаемся к элементу, который стоит перед элементом, который необходимо удалить
	for(int i = 0;i<pos - 1;++i) {
		temp_head = temp_head->Next;
	}

	//перебрасываемя указатель Next: было a->b->c станет a->c и b отдельно, делаем резрвную копию b
	Element* temp = temp_head->Next;
	char res = temp->data;
	temp_head->Next = temp_head->Next->Next;
	delete temp;
	return res;
}
// Тестовый пример
void main()
{
   // Создаем объект класса List
   List lst;

   // Тестовая строка
   char s[] = "Hello, World !!!\n";
   // Выводим строку
   cout << s << "\n\n";
   // Определяем длину строки
   int len = strlen(s);
   // Загоняем строку в список
   for(int i = 0; i < len; i++)
      lst.Add(s[i]);
   // Распечатываем содержимое списка
   lst.Print();
   // Удаляем три элемента списка
   lst.Del();
   lst.Del();
   lst.Del();
   //Распечатываем содержимое списка
   lst.Print();

   //Вставляем 3-й символ, согласно нумерации массива с нуля
   lst.Insert('+',2);
   lst.Print();

   //удаляем 3-й символ
   lst.Delete(2);
   lst.Print();

   //находим позицию элемента 'l'
   cout<<"First position of 'l': "<<lst.Search('l')<<endl<<endl;
}


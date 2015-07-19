#include <iostream>
using namespace std;
 

struct Element
{
   // ������
   char data;
   // ����� ���������� �������� ������
   Element * Next;
};

// ����������� ������
class List
{
   // ����� ��������� �������� ������
   Element * Head;
   // ����� ��������� �������� ������
   Element * Tail;
   // ���������� ��������� ������
   int Count;

public:
   // �����������
   List();
   // ����������
   ~List();
	
   // ���������� �������� � ������
   // (����� ������� ���������� ���������)
   void Add(char data);
	
   // �������� �������� ������
   // (��������� �������� �������)
   void Del();
   // �������� ����� ������
   void DelAll();
	
   // ���������� ����������� ������
   // (���������� ���������� � ��������� ��������)
   void Print();
	
   // ��������� ���������� ���������, ����������� � ������
   int GetCount();

   // ������� �������� � �������� �������
   void Insert(char data, int pos);

   //�������� �������� �� �������� �������
   char Delete(int pos);

   //����� ��������� ��������
   int Search(char data);
};

List::List()
{
   // ���������� ������ ����
   Head = Tail = NULL;   
   Count = 0;
}

List::~List()
{
   // ����� ������� ��������
   DelAll();
}

int List::GetCount()
{
   // ���������� ���������� ���������
   return Count;
}

void List::Add(char data)
{
   // �������� ������ ��������
   Element * temp = new Element;

   // ���������� �������
   temp->data = data;
   // ��������� ������� �����������
   temp->Next = NULL;
   // ����� ������� ���������� ��������� ��������� ������
   // ���� �� �� ������ �����������
   if(Head!=NULL){
		Tail->Next=temp;
		Tail = temp;
		++Count;
   }
   // ����� ������� ���������� ������������
   // ���� �� ������ �����������
   else{
	   Head=Tail=temp;
	   ++Count;
   }
}

void List::Del()
{
   // ���������� ����� ��������� ��������
   Element * temp = Head;
   // ������������� ������ �� ��������� �������
   Head = Head->Next;
   // ������� ������ �������� �������
   delete temp;
}

void List::DelAll()
{
   // ���� ��� ���� ��������
   while(Head != 0)
      // ������� �������� �� ������
      Del();
}

void List::Print()
{
   // ���������� ����� ��������� ��������
   Element * temp = Head;
   // ���� ��� ���� ��������
   while(temp != 0)
   {
      // ������� ������
      cout << temp->data << " ";
      // ��������� �� ��������� �������
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
		//������ temp_head ��������� �� �������� ����� �������� ������� ����� �������
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

		//���� ��������� � �����, �� ���� �������� �����
		

		//����������� ����������
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

	//������������ � ��������, ������� ����� ����� ���������, ������� ���������� �������
	for(int i = 0;i<pos - 1;++i) {
		temp_head = temp_head->Next;
	}

	//�������������� ��������� Next: ���� a->b->c ������ a->c � b ��������, ������ �������� ����� b
	Element* temp = temp_head->Next;
	char res = temp->data;
	temp_head->Next = temp_head->Next->Next;
	delete temp;
	return res;
}
// �������� ������
void main()
{
   // ������� ������ ������ List
   List lst;

   // �������� ������
   char s[] = "Hello, World !!!\n";
   // ������� ������
   cout << s << "\n\n";
   // ���������� ����� ������
   int len = strlen(s);
   // �������� ������ � ������
   for(int i = 0; i < len; i++)
      lst.Add(s[i]);
   // ������������� ���������� ������
   lst.Print();
   // ������� ��� �������� ������
   lst.Del();
   lst.Del();
   lst.Del();
   //������������� ���������� ������
   lst.Print();

   //��������� 3-� ������, �������� ��������� ������� � ����
   lst.Insert('+',2);
   lst.Print();

   //������� 3-� ������
   lst.Delete(2);
   lst.Print();

   //������� ������� �������� 'l'
   cout<<"First position of 'l': "<<lst.Search('l')<<endl<<endl;
}


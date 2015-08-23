#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

int is_exist_in_arr(int data, int* arr, int length) {
	for(int i = 0;i<length;++i) {
		if(arr[i] == data) {
			return 1;
		}
	}
	return 0;
}

string fgets_string(FILE* f, char marker) {
	string res;
	char* str = new char[50];
	int i = 0;
	char ch;
	for(;;) {
		ch = fgetc(f);
		
		if(ch == marker) {
			str[i] = '\0';
			break;
		}
		else {
			str[i++] = ch;
		}
	}
	res = str;
	return str;

}

void fwrite_string(const string& str, FILE* f) {
	char* ch_str = new char[str.length()];
	unsigned int i;
	for(i = 0;i<str.length(); ++i) {
		ch_str[i] = str[i];
	}
	ch_str[i] = '\0';
	fputs(ch_str, f);
	fputc('$',f);
}

int strtolower(string str) {
	unsigned int i = 0;
	while(i<str.length()) {
		tolower(str[i++]);
	}
	return 1;
}

int feof_star(FILE* f) {
	if(feof(f)) {
		return 1;
	}
	else {
		int pos = ftell(f);
		fgetc(f);
		if(feof(f)) {
			return 1;
		}
		fseek(f, pos, SEEK_SET);
	}
	return 0;
}

/*Tel - телефонная книга, tel - телефон*/
class Tel {
private:
	static int id;
	typedef struct Record {
		int id;
		string name;
		string surname;
		string father_name;
		string telephone;
		string address;
		struct Record* next;
		struct Record* prev;
		

		Record(int _id, string _name, string _surname, string _father_name, string _telephone, string _address) {
			//грубо, но всё равно пришлось бы это делать, просто с возвратом к тому, что было - двойная работа
			strtolower(_name);
			strtolower(_surname);
			strtolower(_father_name);
			strtolower(_telephone);
			strtolower(_address); 

			this->id = _id;
			this->name = _name;
			this->surname = _surname;
			this->father_name = _father_name;
			this->telephone = _telephone;
			this->address = _address;
		}
	} record;

	record* abonent;
	record* last;
	int amount;
public:
	Tel();
	~Tel();

	void add(string, string, string, string, string);
	void remove(int id);
	void change(int id, string, string, string, string, string);
	void search(char mode, string data); //in search mode defines the data
	void print(char mode);
	void print(char mode, string data_bot, string data_top); //<-in this print mode defines data_bot and data_top
	record* getById(int id) {
		record* temp = abonent;
		while(temp!=nullptr) {
			if(temp->id == id) {
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}
	void save();
	void load();
};

Tel::Tel() {
	abonent  = nullptr;
	last = nullptr;
	amount = 0;
}

Tel::~Tel() {
	record* temp = last;
	record* temp2;
	while(temp!=nullptr) {
		temp2 = temp->prev;
		delete temp;
		temp = temp2;
	}
}

void Tel::add(string name, string surname, string father_name, string telephone, string address) {
	

	if(amount == 0) {
		abonent = new Record(amount, name, surname, father_name, telephone, address);
		abonent->next = nullptr;
		abonent->prev = nullptr;
		last = abonent;
	}
	else {
		record* temp = abonent;
		record* prev;
		while(temp!=nullptr) {
			prev = temp;
			temp = temp->next;
		}
		temp = new Record(amount, name, surname, father_name, telephone, address);
		temp->next = nullptr;
		temp->prev = prev;
		temp->prev->next = temp;
		last = temp;
	}
	++amount;
}

void Tel::remove(int id) {
	record* temp = abonent;
	while(temp!=nullptr) {
		if(temp->id == id) {
			if(temp->next) {
				record* temp_id = temp->next;
				while(temp_id != nullptr) {
					--(temp_id->id);
					temp_id = temp_id->next;
				}
				temp->next->prev = temp->prev;
			}
			if(temp->prev) {
				temp->prev->next = temp->next;
			}
			if(temp->id == 0) {
				abonent = temp->next;
			}
			if(temp->id == amount - 1) {
				last = temp->prev;
			}
			delete temp;
			--amount;
			break;
		}
		temp = temp->next;
	}
	if(temp == nullptr) {
		throw "Hasn't found record with this id";
	}
}

void Tel::print(char mode) {
	switch(mode) {
	case 'n':
		if(amount == 0) {
			throw "Empty database";
		}
		record* temp;
		temp = abonent;
		cout<<"id Name\tSurname\tFather name\tTelephone\tAddress\n";
		while(temp!=nullptr) {
			cout<<temp->id<<"  "<<temp->name<<"\t"<<temp->surname<<"\t"<<temp->father_name<<"\t\t"<<temp->telephone<<"\t"<<temp->address<<"\n";
			temp = temp->next;
		}
		cout<<endl<<endl;
		break;
	}
}

void Tel::print(char mode, string data_bot, string data_top) {
	
	strtolower(data_bot);
	strtolower(data_top);
	if(amount == 0) {
		cout<<endl<<"Empty database, can't find anything"<<endl<<endl;
	}
	string id; //the row for id, that already printed
	int* id_arr = new int[amount];
	int j;
	for(j = 0;j<amount; ++j) {
		id_arr[j] = -1;
	}
	j = 0;
	record* temp = abonent;
	switch(mode) {
		case 's':
			//1)Создать массив интересующих id
			while(temp!=nullptr) {
				if(temp->surname>=data_bot && temp->surname<=data_top) {
					id_arr[j++] = temp->id;
				}
				temp = temp->next;
			}
			if(j == 0) {
				cout<<endl<<"Haven't found records that are suit to this range"<<endl<<endl;
				return;
			}
			//2)отсортировать в этом массиве id по алфавиту
			for(int i = 0;i<j;++i) {
				for(int k = 0; k<j; ++k) {
					if(getById(id_arr[i])->surname < getById(id_arr[k])->surname) {
						int temp = id_arr[i];
						id_arr[i] = id_arr[k];
						id_arr[k] = temp;
					}
				}
			}
			//3)Вывести всё, что получилось
			cout<<"id Name\tSurname\tFather name\tTelephone\tAddress\n";
			for(int i = 0;i<j;++i) {
				cout<<getById(id_arr[i])->id<<"  "<<getById(id_arr[i])->name<<"\t"<<getById(id_arr[i])->surname<<"\t"<<getById(id_arr[i])->father_name<<"\t\t"<<getById(id_arr[i])->telephone<<"\t"<<getById(id_arr[i])->address<<"\n";
			}
			break;
		case 't':
			//1)Создать массив интересующих id
			while(temp!=nullptr) {
				if(temp->telephone>=data_bot && temp->telephone<=data_top) {
					id_arr[j++] = temp->id;
				}
				temp = temp->next;
			}
			if(j == 0) {
				cout<<endl<<"Haven't found records that are suit to this range"<<endl<<endl;
				return;
			}
			//2)отсортировать в этом массиве id по алфавиту
			for(int i = 0;i<j;++i) {
				for(int k = 0; k<j; ++k) {
					if(getById(id_arr[i])->telephone < getById(id_arr[k])->telephone) {
						int temp = id_arr[i];
						id_arr[i] = id_arr[k];
						id_arr[k] = temp;
					}
				}
			}
			//3)Вывести всё, что получилось
			cout<<"id Name\tSurname\tFather name\tTelephone\tAddress\n";
			for(int i = 0;i<j;++i) {
				cout<<getById(id_arr[i])->id<<"  "<<getById(id_arr[i])->name<<"\t"<<getById(id_arr[i])->telephone<<"\t"<<getById(id_arr[i])->father_name<<"\t\t"<<getById(id_arr[i])->telephone<<"\t"<<getById(id_arr[i])->address<<"\n";
			}
			break;
	}
	delete[] id_arr;
}

void Tel::change(int id, string name, string surname, string father_name, string telephone, string address) {
	record* temp = abonent;
	while(temp!=nullptr) {
		if(temp->id == id) {
			temp->name = name;
			temp->surname = surname;
			temp->father_name = father_name;
			temp->telephone = telephone;
			temp->address = address;
			break;
		}
		temp = temp->next;
	}
	if(temp == nullptr) {
		throw "Hasn't found record with this id";
	}
}

void Tel::search(char mode, string data) {
	
	record* temp;
	int gate = 0;
	switch(mode) {
	case 't':
		temp = abonent;
		while(temp!=nullptr) {
			if(temp->telephone == data) {
				if(!gate) {
					cout<<"id Name\tSurname\tFather name\tTelephone\tAddress\n";
					gate = 1;
				}
				cout<<temp->id<<"  "<<temp->name<<"\t"<<temp->surname<<"\t"<<temp->father_name<<"\t\t"<<temp->telephone<<"\t"<<temp->address<<"\n";
			}
			temp = temp->next;
		}
		break;
	case 's':
		temp = abonent;
		while(temp!=nullptr) {
			if(temp->surname == data) {
				if(!gate) {
					cout<<"id Name\tSurname\tFather name\tTelephone\tAddress\n";
					gate = 1;
				}
				cout<<temp->id<<"  "<<temp->name<<"\t"<<temp->surname<<"\t"<<temp->father_name<<"\t\t"<<temp->telephone<<"\t"<<temp->address<<"\n";
			}
			temp = temp->next;
		}
		break;
	}
	
	if(!gate) {
		cout<<endl<<"Hasn't found record with this id"<<endl;
	}

}

void Tel::save() {
	record* temp = abonent;
	FILE* f = fopen("book.txt","wb");
	if(!f) {
		throw "Can not to open the file \"book.txt\"";
	}
	while(temp!=nullptr) {
		fwrite_string(temp->name, f);
		fwrite_string(temp->surname, f);
		fwrite_string(temp->father_name, f);
		fwrite_string(temp->telephone, f);
		fwrite_string(temp->address, f);
		temp = temp->next;
	}
}

void Tel::load() {
	FILE* f = fopen("book.txt","rb");
	if(!f) {
		throw "Can not to open the file \"book.txt\"";
	}
	string _name, _surname, _father_name, _telephone, _address;
	while(!feof_star(f)) {
		_name = fgets_string(f, '$');
		_surname = fgets_string(f, '$');
		_father_name = fgets_string(f, '$');
		_telephone = fgets_string(f, '$');
		_address = fgets_string(f, '$');

		this->add(_name, _surname, _father_name, _telephone, _address);
	}
}

int main() {

	Tel book;
	//сначала выполнить программу один, чтобы в файл записалась книга абонентов
	//потом раскоментировать три строчки и посмотреть , что загрузка работает
	/*book.load();
	book.print('n');
	return 0;*/
	try {
		//book.print('n'); //раскомментировать, чтобы посмотреть работу throw пустая база данных
		book.add("Nik", "B", "Fn", "+375 ****", "ulica 15");
		book.add("Igor","A", "Fn", "+375 ****", "ulica 18");
		book.add("Nek", "C", "Nf", "+XXX ****", "secret **");
		book.save();
		book.print('n');
		book.change(1,"New", "D", "W", "new telephone", "new address");
		book.print('n');
		cout<<endl<<"Search:"<<endl;
		book.search('t',"+375 ****");
		cout<<endl<<"End search"<<endl;
		book.print('n');
		cout<<endl<<"Filter:"<<endl;
		book.print('s', "A","B");
		cout<<endl<<"End filter."<<endl;
		book.remove(1);
		book.print('n');
		book.remove(0);
		book.print('n');
		book.remove(0);
		//book.remove(0); //раскомментировать, чтобы посмотреть работу throw такой id не найден
		book.print('n');
		
	}
	catch(char* err) {
		cout<<endl<<err<<endl<<endl;
	}

	return 0;
}

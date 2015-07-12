#include <iostream>
#include <string>
using namespace std;

class Passport;
class Foreign_Passport;

class Passport {
protected:
	string name;
	string surname;
	string father_name;
	int id;
	int verififcation_number;
	string adress;
	string who_give;
public:
	Passport() = default;
	void set(string name, string surname, string father_name, int id, int verification_number, string adress, string who_give){
		this->name = name;
		this->surname = surname;
		this->father_name = father_name;
		this->id = id;
		this->verififcation_number = verification_number;
		this->adress = adress;
		this->who_give = who_give;
	}
	void show(){
		cout << "Information about citiezen" << endl;
		cout << "Name: " << name << endl;
		cout << "Surname: " << surname << endl;
		cout << "Father_name: "<< father_name << endl;
		cout << "id: " << id << endl;
		cout << "verification_number: " << verififcation_number << endl;
		cout << "adress: " << adress << endl;
		cout << "who_give" << who_give << endl;
	}
};

class Foreign_Passport: protected Passport {
protected:
	string visa;
	int foreign_id;
public:
	Foreign_Passport() = default;
	Foreign_Passport(Passport up, string uvisa, int uforeign_id) :Passport(up), visa(uvisa), foreign_id(uforeign_id){}
	void set(string name, string surname, string father_name, int id, int verification_number, string adress, string who_give, string visa, int foreign_id){
		Passport::set(name, surname, father_name, id, verification_number, adress, who_give);
		this->visa = visa;
		this->foreign_id = foreign_id;
	}
	void show() {
		Passport::show();
		cout << "visa: " << visa << endl;
		cout << "foreign_id: " << id << endl;
	}
};

int main() {
	Passport p;
	p.set("Vasya", "Pupkin", "Vasilievich", 12345678, 47896321452, "Bikova 14", "Fantasy RUVD");
	p.show();
	cout << endl;

	Foreign_Passport for_p(p,"Random visa", 1255698);
	for_p.show();

	cout << endl;
	return 0;
}

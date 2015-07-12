#include <iostream>
#include <string>
using namespace std;

class Student {
protected:
	string name;
public:
	Student() : name("Undef"){}
	Student(const string& n) :name(n){}
	void show() { cout << name; }
	void set_name(const string& new_name) { name = new_name; }
};

class Aspirant: public Student { 
private:
	int experience;
public:
	Aspirant() :Student(), experience(0){}
	Aspirant(const string& name) :Student(name), experience(0){}
	Aspirant(const string& name, int exp) :Student(name), experience(exp){}
	int& exp() { return experience; }
	void show() {
		Student::show();
		cout <<" "<<experience<<endl;
	}
};



int main() {

	Aspirant asp;
	asp.show();
	Aspirant asp2("Asp", 5);
	asp2.show();

	cout << endl;
	return 0;
}

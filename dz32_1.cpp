#include <iostream>
using namespace std;

class Employer {
public:
	virtual void print() = 0;
};

class President : public virtual Employer {
	public:
	virtual void print() {
		cout<<"I am a president";
	}
};

class Manager : public virtual Employer {
	public:
	virtual void print() {
		cout<<"I am a manager";
	}
};

class Worker : public virtual Employer {
	public:
	virtual void print() {
		cout<<"I am a worker";
	}
};

int main() {
	Employer* empl;
	Manager man;
	empl = &man;
	empl->print();
	cout<<endl<<endl;
}
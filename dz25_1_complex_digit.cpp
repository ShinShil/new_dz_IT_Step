#include <iostream>
using namespace std;

class Complex {
private:
	double real;
	double imaginary;
	double module;
	double sinus;
	double cosinus;
public:
	Complex();
	Complex(double, double);
	Complex(const Complex&);
	~Complex();

	void print_alg();
	void print_trig();
	void print_exp();

	Complex& operator=(const Complex&);
	Complex operator+(const Complex&);
	Complex operator-(const Complex&);
	Complex operator*(const Complex&);
	Complex operator/(const Complex&);

	friend istream& operator>>(istream&, Complex&);
	friend ostream& operator<<(ostream&, const Complex&);
};

Complex::Complex() {
	real = 0 ;
	imaginary = 0 ;
	module = 0 ;
	sinus = 0 ;
	cosinus	 = 0 ;
}
Complex::Complex(double real, double imaginary) {
	this->real = real;
	this->imaginary = imaginary;
	module = sqrt(real*real + imaginary*imaginary);
	if(real>0){
		sinus = sin(atan(imaginary/real));
		cosinus = sqrt(1 - sinus*sinus);
	}
	else if(real<0 && imaginary>0){
		sinus = sin(atan(imaginary/real + 3.14));
		cosinus = sqrt(1 - sinus*sinus);
	}
	else if(real<0 && imaginary<0) {
		sinus = sin(atan(imaginary/real - 3.14));
		cosinus = sqrt(1 - sinus*sinus);
	}
	else if(imaginary!= 0 && real == 0) {
		real = 0;
		imaginary = 0;
		sinus = 0;
		cosinus = 0;
		module = 0;
	}
	else if(imaginary == 0) {
		sinus = 0;
		cosinus = 1;
	}
}
Complex::Complex(const Complex& cpx_dig) {
	real  = cpx_dig.real;
	imaginary = cpx_dig.imaginary;
	sinus = cpx_dig.sinus;
	cosinus = cpx_dig.cosinus;
	module  = cpx_dig.module; 
}
Complex::~Complex() {

}

void Complex::print_alg() {
	if(imaginary>=0)
		cout<<"Algebr phorm: "<<real<<" + "<<imaginary<<"*i";
	else
		cout<<cout<<"Algebr phorm: "<<real<<" + ("<<imaginary<<")*i";
}
void Complex::print_trig() {
	cout<<"Trignometric phorm: "<<module<<" * (sin("<<asin(sinus)<<") + cos("<<acos(cosinus)<<")";
}
void Complex::print_exp() {
	cout<<"Exponent form: z = "<<module<<"*e^(i*"<<asin(sinus)<<")";
}

Complex& Complex::operator=(const Complex& cpx_dig) {
	if(this == &cpx_dig) {
		return *this;
	}
	real  = cpx_dig.real;
	imaginary = cpx_dig.imaginary;
	sinus = cpx_dig.sinus;
	cosinus = cpx_dig.cosinus;
	module  = cpx_dig.module; 
	return *this;
}
Complex Complex::operator+(const Complex& second_obj) {
	return Complex(real + second_obj.real, imaginary + second_obj.imaginary);
}
Complex Complex::operator-(const Complex& second_obj) {
	return Complex(real - second_obj.real, imaginary - second_obj.imaginary);
}
Complex Complex::operator*(const Complex& second_obj) {
	double tmp_real = (real * second_obj.real - imaginary * second_obj.imaginary);
	double tmp_imaginary = (imaginary * second_obj.real + real * second_obj.imaginary);
	return Complex(tmp_real, tmp_imaginary);
}
Complex Complex::operator/(const Complex& second_obj) {
	if(!second_obj.module)
		return Complex();
	double tmp_real = (real * second_obj.real + imaginary * second_obj.imaginary)/(real*real + second_obj.real * second_obj.real);
	double tmp_imaginary = (imaginary * second_obj.real - real * second_obj.imaginary)/(real*real + second_obj.real * second_obj.real);
	return Complex(tmp_real, tmp_imaginary);
}

istream& operator>>(istream& is, Complex& cpx_dig) {
	int tmp_real, tmp_imaginary;

	cout<<"Real: ";
	cin >>tmp_real;
	cout<<"\b";
	cout<<"Imaginary: ";
	cin>>tmp_imaginary;
	cout<<"\b";
	cpx_dig = Complex(tmp_real, tmp_imaginary);

	return is;
}
ostream& operator<<(ostream& os, const Complex& cpx_dig) {
	if(cpx_dig.imaginary>=0)
		cout<<cpx_dig.real<<" + "<<cpx_dig.imaginary<<"*i";
	else
		cout<<cpx_dig.real<<" + ("<<cpx_dig.imaginary<<")*i";

	return os;
}

int main() {
	Complex test1(1,2);
	Complex test2(2,2);
	cout<<"Complex digit 1: "<<test1<<endl<<"Complex digit 2: "<<test2<<endl<<endl;
	Complex summ = test1 + test2;

	cout<<"Their summ in three forms"<<endl;
	summ.print_alg();
	cout<<endl;
	summ.print_exp();
	cout<<endl;
	summ.print_trig();
	cout<<endl<<endl;

	cout<<"Their difference: "<<test1 - test2<<endl<<endl;
	cout<<"Their multiplication: "<<test1 * test2<<endl<<endl;
	cout<<"Their didvision: "<<test1 / test2<<endl<<endl;
	cout<<endl;
	return 0;
}
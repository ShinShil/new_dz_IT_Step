#include <iostream>
using namespace std;

class Array {
private:
	enum {
		TRUE = 1,
		FALSE = 0
	};
	int* arr;
	int col;
	int init;
public:
	Array();
	Array(int);
	Array(const Array&);
	~Array();

	void clean();
	void set_mem(int);

	Array& operator=(const Array&);
	Array operator+(const Array&);
	Array operator-(const Array&);
	Array& operator++();
	Array& operator--();
	Array& operator++(int k);
	Array& operator--(int k);
	int& operator[](int);
	friend istream& operator>>(istream&, Array&);
	friend ostream& operator<<(ostream&, const Array&);
};

Array::Array() {
	arr = nullptr;
	col = 0;
	init = FALSE;
}

Array::Array(int amount){
	arr = (int*)malloc(sizeof(int)*amount);
	col = amount;
	init = FALSE;
}

void Array::set_mem(int amount) {
	if(arr!=nullptr) {
		clean();
	}
	arr = (int*)malloc(sizeof(int)*amount);
	col = amount;
	init = FALSE;
}

Array::Array(const Array& old) {
	if(old.arr!=nullptr){
		arr = (int*)malloc(sizeof(int)*old.col);
		col = old.col;
		if(old.init == TRUE) {
			for(int i = 0; i < col; ++i) {
				if(old.arr[i])
					arr[i] = old.arr[i];
			}
		}
	}
	else {
		arr = nullptr;
		col = 0;
	}
	init = old.init;
}

Array::~Array() {
	if(arr != nullptr) {
		free(arr);
	}
}

istream& operator>>(istream& is, Array& enter) {
	if(enter.arr == nullptr) {
		fflush(stdin);
		return is;
	}
	else {
		for(int i = 0;i<enter.col;++i) {
			cin>>enter.arr[i];
		}
		enter.init = 1;
		return is;
	}
}

ostream& operator<<(ostream& os, const Array& out) {
	if(!out.init) {
		return os;
	}
	else {
		for(int i = 0;i<out.col;++i) {
			cout<<out.arr[i]<<" ";
		}
		cout<<"\b";
		return os;
	}
}

int& Array::operator[](int index) {
	if(arr != nullptr && index<col) {
		if(!init) {
			init = 1;
		}
		return arr[index];
	}
	else {
		if(init == TRUE) {
			return arr[0];
		}
		else {
			arr = (int*)malloc(sizeof(int));
			arr[0] = 0;
			return arr[0];
		}
	}
}

Array& Array::operator=(const Array& old) {
	
	if(this == &old) {
		return *this;
	}

	if(arr!=nullptr) {
		free(arr);
	}

	if(old.arr!=nullptr){
		arr = (int*)malloc(sizeof(int)*old.col);
		col = old.col;
		if(old.init == TRUE) {
			for(int i = 0; i < col; ++i) {
				if(old.arr[i])
					arr[i] = old.arr[i];
			}
		}
	}
	else {
		arr = nullptr;
		col = 0;
	}

	init = old.init;
	return *this;
}

Array Array::operator+(const Array& second_obj) {
	if(init && second_obj.init) {
		if(col!=second_obj.col) {
			Array error;
			return error;
		}
		Array res(col);
		for(int i = 0;i<col;++i) {
			res[i] = arr[i] + second_obj.arr[i];
		}
		res.init = TRUE;
		return res;
	}
	else {
		Array error;
		return error;
	}
}

Array Array::operator-(const Array& second_obj) {
	if(init && second_obj.init) {
		if(col!=second_obj.col) {
			Array error;
			return error;
		}
		Array res(col);
		for(int i = 0;i<col;++i) {
			res[i] = arr[i] - second_obj.arr[i];
		}
		res.init = TRUE;
		return res;
	}
	else {
		Array error;
		return error;
	}
}

void Array::clean() {
	free(arr);
	arr = nullptr;
	col = 0;
	init = FALSE;
}

Array& Array::operator++() {
	Array temp = *this;
	clean();
	++temp.col;
	*this = temp;
	return *this;
}

Array& Array::operator++(int k) {
	Array res = *this;
	Array temp = *this;
	clean();
	++temp.col;
	*this = temp;
	return res;
}

Array& Array::operator--() {
	Array temp = *this;
	clean();
	if(temp.col>1)
		--temp.col;
	*this = temp;
	return *this;
}

Array& Array::operator--(int k) {
	Array res = *this;
	Array temp = *this;
	clean();
	if(temp.col>1)
		--temp.col;
	*this = temp;
	return res;
}

int main() {
	Array t(3);
	
	Array a(3);
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	Array b(3);
	b[0] = 4;
	b[1] = 5;
	b[2] = 6;

	cout<<"Enter array(3 elements): ";
	cin>>t;
	cout<<"Your array: "<<t<<endl<<endl;

	cout<<"a: "<<a<<"\nb: "<<b<<endl;
	Array c = a+b;
	cout<<"a + b = {"<<c<<"}"<<endl;

	Array incr;
	incr = c;
	(++incr)[3] = 5;
	cout<<endl<<endl<<"New summ after dynamic incriment: "<<incr<<endl;
}
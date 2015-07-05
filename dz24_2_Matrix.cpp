#include <iostream>
using namespace std;

class Matrix;

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
	friend Matrix;
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

class Matrix {
private:
	Array* m_arr;
	int row;
	int col;
public:
	Matrix();
	Matrix(int, int);
	Matrix(const Matrix&);
	~Matrix();

	void clean();
	void print_matrix();
	void enter_matrix();

	Array& operator[](int);
	Matrix& operator=(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix operator~();
};

Matrix::Matrix() {
	m_arr = nullptr;
	row = 0;
	col = 0;
}

Matrix::Matrix(int row, int col) {
	m_arr = (Array*)malloc(sizeof(Array)*row);
	for(int i = 0; i<row; ++i) {
		m_arr[i].arr = nullptr;
		m_arr[i].set_mem(col);
	}
	this->row = row;
	this->col = col;
}

Matrix::Matrix(const Matrix& old) {
	row = old.row;
	col = old.col;
	m_arr = (Array*)malloc(sizeof(Array)*row);
	for(int i = 0; i<row; ++i) {
		for(int j = 0;j<col;++j) {
			m_arr[i].arr = nullptr;
			m_arr[i] = old.m_arr[i];
		}
	}
}

void Matrix::clean() {
	if(m_arr==nullptr) {
		return;
	}
	for(int i = 0;i<row;++i) {
		m_arr[i].clean();
	}
	col = 0;
	row = 0;
	free(m_arr);
	m_arr = nullptr;
}

void Matrix::enter_matrix() {
	for(int i = 0;i<row;++i) {
		cout<<"Row "<<i + 1<<": ";
		cin>>m_arr[i];
		while(getchar()!='\n');
	}
}

void Matrix::print_matrix() {
	for(int i = 0;i<row;++i) {
		cout<<m_arr[i]<<endl;
	}
}

Array& Matrix::operator[](int index) {
	return m_arr[index];
}

Matrix::~Matrix() {
	clean();
}

Matrix& Matrix::operator=(const Matrix& old) {
	if(this == &old) {
		return *this;
	}

	if(m_arr!=nullptr) {
		this->clean();
	}

	if(old.m_arr == nullptr) {
		m_arr = nullptr;
		row = old.row;
		col = old.col;
		return *this;
	}

	row = old.row;
	col = old.col;
	m_arr = (Array*)malloc(sizeof(Array)*row);
	for(int i = 0; i<row; ++i) {
		m_arr[i].arr = nullptr;
		m_arr[i] = old.m_arr[i];
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& second_obj) {
	if(row!=second_obj.row || col!=second_obj.col || m_arr == nullptr || second_obj.m_arr == nullptr) {
		Matrix empty_res;
		return empty_res;
	}
	Matrix res(row, col);
	for(int i = 0;i<row;++i){
		if(m_arr[i].init == 0 || second_obj.m_arr[i].init == 0) {
			Matrix empty_res;
			res.clean();
			return empty_res;
		}
		res.m_arr[i] = m_arr[i] + second_obj.m_arr[i];
	}
	return res;	
}

Matrix Matrix::operator-(const Matrix& second_obj) {
	if(row!=second_obj.row || col!=second_obj.col || m_arr == nullptr || second_obj.m_arr == nullptr) {
		Matrix empty_res;
		return empty_res;
	}
	Matrix res(row, col);
	for(int i = 0;i<row;++i){
		if(m_arr[i].init == 0 || second_obj.m_arr[i].init == 0) {
			Matrix empty_res;
			res.clean();
			return empty_res;
		}
		res.m_arr[i] = m_arr[i] - second_obj.m_arr[i];
	}
	return res;	
}

Matrix Matrix::operator*(const Matrix& second_obj) {
	if(col!=second_obj.row || m_arr == nullptr || second_obj.m_arr == nullptr) {
		Matrix empty_res;
		return empty_res;
	}
	Matrix res(row, second_obj.col);
	for(int i = 0;i<res.row;++i){
		if(m_arr[i].init == 0 || second_obj.m_arr[i].init == 0) {
			Matrix empty_res;
			res.clean();
			return empty_res;
		}
		for(int j = 0;j<res.col;++j) {
			int test = 0;
			res.m_arr[i][j] = 0;
			for(int k = 0; k<row; ++k) {
				res.m_arr[i][j] = res[i][j] + (m_arr[i][k] * second_obj.m_arr[k][j]);
				test = res.m_arr[i][j];
			}
		}
	}
	return res;	
}

Matrix Matrix::operator~() {
	if(m_arr == nullptr) {
		Matrix empty_res;
		return empty_res;
	}

	Matrix res(col,row);
	for(int i = 0; i<row; ++i) {
		for(int j = 0; j<col; ++j) {
			res.m_arr[j][i] = m_arr[i][j];
		}
	}

	*this = res;
	return *this;
}


int main() {
	Matrix m1(3,3);
	
	cout<<"Enter matrix(the size 3X3)"<<endl;
	m1.enter_matrix();
	cout<<endl<<"Your matrix:"<<endl;
	m1.print_matrix();
	cout<<endl<<"Element[0][0]: "<<m1[0][0]<<endl;

	Matrix m2 = m1;
	cout<<endl<<"Copy of matrix"<<endl;
	m2.print_matrix();
	cout<<endl<<"Their summ"<<endl;
	(m2+m1).print_matrix();

	Matrix m3(3,3);
	Matrix m4(3,2);
	Matrix m5;
	m3[0][0] = 1; m3[0][1] = 2; m3[0][2] = -1;
	m3[1][0] = 3; m3[1][1] = 4; m3[1][2] = 0;
	m3[2][0] = -1; m3[2][1] = 2; m3[2][2] = -2;
	m4[0][0] = 3; m4[0][1] = -2;
	m4[1][0] = 1; m4[1][1] = 0;
	m4[2][0] = 4; m4[2][1] = -3;
	m5 = m3*m4;
	cout<<endl<<"Matrix m3"<<endl;
	m3.print_matrix();
	cout<<"Matrix m4"<<endl;
	m4.print_matrix();
	cout<<"The result if their multypling"<<endl;
	m5.print_matrix();

	cout<<endl<<"Transpone multyply result"<<endl;
	(~m5).print_matrix();
	cout<<endl;
	return 0;
}
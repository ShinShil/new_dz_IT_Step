#include <iostream>
using namespace std;

// класс "точка"
class Point{

	// кооординаты
	int X;
	int Y;
public:

	//конструктор
	Point(){
		X = Y = 0;
	}

	//установка координат
	void SetPoint(int iX, int iY){
		X = iX;
		Y = iY;
	}

	//демонстрация координат
	void Show(){
		cout<< "----------------------------\n\n";
		cout<< X<< "\t"<< Y<< "\n\n";
		cout<< "----------------------------\n\n";
	}
};
//класс фигура
class Figura{

	// агрегация точки
	// (координаты углов)
	Point*obj;

	// количество углов
	int count;
	// цвет фигуры
	int color;

public:

	//конструктор
	Figura(){
		count = color = 0;
		obj = NULL;
	}

	// создание фигуры
	void CreateFigura(int cr, int ct){
		// если углов меньше трех - это не фигура
		if (ct< 3) exit(0);
		//инициализация цвета и количества углов
		count = ct;
		color = cr;
		// выдделение памяти под массив точек
		obj = new Point[count];
		if (!obj) exit(0);

		//установка координат точек
		int tempX, tempY;
		for (int i = 0; i< count; i++){
			cout<< "Set X\n";
			cin>> tempX;
			cout<< "Set Y\n";
			cin>> tempY;
			obj[i].SetPoint(tempX, tempY);
		}
	}

	//показ фигуры
	void ShowFigura(){
		cout<< "----------------------------\n\n";
		cout<< "Color"<< color<< "\n\nPoints - "<< count<< "\n\n";
		for (int i = 0; i< count; i++){
			obj[i].Show();
		}
	}

	~Figura(){
		if (obj != NULL) delete[]obj;
	}


};

/*
Пример фигуры
///
/ /
///////
/     /
/     /
///////
такая фигура состоит из двух квадратов
*/
class Difficult_fig_rect {
public:
	//массив фигур, композиция
	
	Figura* fig;
	//количество составляющих фигур
	int amount;
	//конструктор
	Difficult_fig_rect() {
		amount = 0;
		fig = NULL;
	}

	//создание сложной фигуры, соста
	void create(int iamount) {
		amount = iamount;
		fig = new Figura[amount];

		for (int i = 0; i < amount; ++i) {
			cout << endl << "Figure "<<i+1 << ":" <<endl;
			fig[i].CreateFigura(4, 4);
		}
	}

	//деструктор
	~Difficult_fig_rect() {
		if (fig != NULL) delete[] fig;
	}
};

int main(){

	Difficult_fig_rect df;
	df.create(2);

	cout << endl;
	return 0;
}

#include <iostream>
using namespace std;

class Circle {
public:
	int radius;
	Circle(int u_r) :radius(u_r){};
	double square(){

		return 3.14*radius*radius;
	}
};

class Square {
public:
	int side;
	Square(int u_s) : side(u_s){};
	double square(){

		return side*side;
	}
};

class Cicle_in_square : public Circle, public Square{
public:
	Cicle_in_square(int u_r, int u_s) :Circle(u_r), Square(u_s){};
	Cicle_in_square(Circle circ, Square sq) :Circle(circ.radius), Square(sq.side){};
	double diff_square(){
		return  Square::square() - Circle::square();
	}
};

int main(){

	Circle circ(5);
	Square sq(10);
	Cicle_in_square circ_in_sq(circ, sq);
	cout << "Circle: radius = 5, square = " << circ.square() << endl;
	cout << "Square: side = 10, square = " << sq.square() << endl;
	cout << "Write this circle in square, the square, that belongs to square, but not to the\ncircle: " << circ_in_sq.diff_square()<<endl;
	cout << endl;
	return 0;
}

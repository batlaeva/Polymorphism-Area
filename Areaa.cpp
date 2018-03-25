// Areaa.cpp: определяет точку входа для консольного приложения.
//найти площадь фигур

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
const double PI = 3.1415;

class Figure {//абстрактный класс
	virtual double area() = 0;//площадь
	virtual void name() = 0;//название фигуры
};

class Square : Figure {
	double a;
public:
	Square(double aa) { a = aa; };
	double area() {
		return a*a;
	};
	void name() {
		cout << "Square" << endl;
	}
};

class Circle : Figure {
	double r;
public:
	Circle(double rr) { r = rr; };
	double area() {
		return PI*r*r;
	};
	void name() {
		cout << "Circle" << endl;
	}
};

class Triangle : Figure {
	double a, b, c;//по формуле герона
public:
	Triangle(double aa, double bb, double cc) { a = aa; b = bb; c = cc; };
	double area() {
		double p = (a + b + c) / 2;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	};
	void name() {
		cout << "Triangle" << endl;
	}
};

class Ellipse : Figure {
	double a, b;
public:
	Ellipse(double aa, double bb) { a = aa; b = bb; };
	double area() {
		return PI*a*b;
	};
	void name() {
		cout << "Ellipse" << endl;
	}
};

class Polygon : Figure {
	vector <double> point;
public:
	Polygon(char* name) {
		ifstream f(name);
		if (!f.is_open())	//проверка на сущёств0ваниё
			cout << "Error: file " << name << " is not found" << endl;
		else {
			char symbol;
			double temp;
			while (!f.eof()) {//пока не конец файла
				f >> temp;
				point.push_back(temp);
				f.get(symbol);//считали текущий символ
				if (symbol == ' ') {
					f >> temp;
					point.push_back(temp);
				}
			}
			f.close();
		}
	};
	double area() {
		double p = 0;
		int i;
		for (i = 0; i <= point.size() - 4; i+=2) {
			p = p + (point[i] * point[i + 3] - point[i + 1] * point[i + 2]);
		}
		// !!!i+=2
		p = abs((p + point[i] * point[1] - point[i + 1] * point[0]) / 2);
		return p;
	};
	void name() {
		cout << "Polygon" << endl;
	}
};

int main()
{
	Square s(4.72);
	s.name();
	cout << s.area() << endl;

	Circle c(5.9);
	c.name();
	cout << c.area() << endl;

	Triangle t(4, 6.2, 9.47);
	t.name();
	cout << t.area() << endl;

	Ellipse e(6, 7.5);
	e.name();
	cout << e.area() << endl;

	Polygon p("polygon.txt");
	p.name();
	cout << p.area();

	_getch();
	return 0;
}


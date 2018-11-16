// Курсавая.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;
class absMatrix
{
protected:
	int N; //размерность матрицы
	unsigned int typesize; //кол-ва байтов типа
public:
	virtual void in();
	virtual void out();
	//friend istream& operator>> (istream&, absMatrix);
	void setDimension(int);
	int getDimension();
	char * getInfo() { return info; }
	void setInfo(char* p) { info = p; }
	absMatrix(absMatrix&);
	absMatrix(int,unsigned int);
	absMatrix();
	~absMatrix();
	absMatrix operator=(absMatrix&);

private:
	char * info;
};

void absMatrix::in()
{
}

void absMatrix::out()
{
}

void absMatrix::setDimension(int p)
{
	this->N = p;
}

int absMatrix::getDimension()
{
	return this->N ;
}

absMatrix::absMatrix(absMatrix &initobj)
{
	this->N = initobj.N;
	this->typesize = initobj.typesize;
	char *temp = new char[this->N*this->N*this->typesize];
	for (int i = 0; i < N*N*this->typesize; i++) {
		temp[i] = initobj.getInfo()[i];
	}
	this->setInfo(temp);
	
}

absMatrix::absMatrix(int p,unsigned int size)
{
	this->typesize = size;
	this->N = p;
	this->info = new char[size*p*p];
	for (int i = 0; i < size*p*p;i++) {
		info[i] = 0;
	}
}

absMatrix::absMatrix()
{
	this->N = 0;
	this->info = 0;
}

absMatrix::~absMatrix()
{
	if (info) delete [] info;
}

absMatrix absMatrix::operator=(absMatrix &sameobj)
{
	return sameobj;
}

class floatMatrix : public absMatrix
{
public:
	floatMatrix() :absMatrix() {};
	floatMatrix(int p) :absMatrix(p,sizeof(float)) {};
	~floatMatrix();
	void in()override;
	void out()override;
private:

};

floatMatrix::~floatMatrix()
{
}
void floatMatrix::in()
{
	float temp;
	cout << "Введите матрицу:\n";
	for (int i = 0; i < N*N; i++) {
		cin >> temp;
		 *(this->getInfo() + i * sizeof(float)) = (float) temp;
	}
}
void floatMatrix::out()
{
	cout << "Вывод матрицы:\n";
	for (int i = 0; i < N; i++) {
		for (int i = 0; i < N; i++) {
			cout << (float) *(this->getInfo() + i * sizeof(float)) << " ";
		}
		cout << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "");
	floatMatrix one(2);
	floatMatrix two(2);
	one.in();
	two.in();
	one.out();
	two.out();
	two = one;
	two.out();
	system("pause");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

//istream & operator>>(istream &R, absMatrix obj)
//{
//	obj.in();
//	return R;
//}

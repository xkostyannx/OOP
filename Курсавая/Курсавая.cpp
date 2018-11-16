#include "pch.h"
#include <iostream>
using namespace std;
class absMatrix
{
protected:
	int N; //размерность матрицы
	unsigned int typesize; //кол-ва байтов типа
public:
	virtual char* give(int,int);
	virtual char* sum(char*,char*);
	virtual char* multiply(char*, char*);
	virtual void insert(char*, char*);
	void setDimension(int);
	int getDimension();
	char * getInfo() { return info; }
	void setInfo(char* p) { info = p; }
	absMatrix(absMatrix&);
	absMatrix(int,unsigned int);
	absMatrix();
	~absMatrix();
	absMatrix& operator=(absMatrix&);
	absMatrix& operator*(absMatrix&);

private:
	char * info;
};



char * absMatrix::give(int, int)
{
	return nullptr;
}

char * absMatrix::sum(char *, char *)
{
	return nullptr;
}

char * absMatrix::multiply(char *, char *)
{
	return nullptr;
}

void absMatrix::insert(char *, char *)
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
	for (unsigned int i = 0; i < N*N*this->typesize; i++) {
		temp[i] = initobj.getInfo()[i];
	}
	this->setInfo(temp);
	
}

absMatrix::absMatrix(int p,unsigned int size)
{
	this->typesize = size;
	this->N = p;
	this->info = new char[size*p*p];
	for (unsigned int i = 0; i < size*p*p;i++) {
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
	this->N = 0;
	this->typesize = 0;
	if (info) delete [] info;
}

absMatrix& absMatrix::operator=(absMatrix &sameobj)
{
	this->~absMatrix();
	
	this->N = sameobj.N;
	this->typesize = sameobj.typesize;
	char *temp = new char[this->N*this->N*this->typesize];
	for (unsigned int i = 0; i < N*N*this->typesize; i++) {
		temp[i] = sameobj.getInfo()[i];
	}
	this->setInfo(temp);

	return *this;
}

absMatrix& absMatrix::operator*(absMatrix &sec)
{
	
	char * temp = new char[this->N*this->N*this->typesize];
	if (this->N != sec.N) cout << "Размерности не совпадают";
	else {
		absMatrix newObj(this->N,this->typesize);
		char * line = new char[this->typesize]{0}; // Сумма всех произведений
		char * sum = new char[this->typesize]{0};	// Промежуточный результат произведения двух элементов матриц
		for (int i = 0; i < this->N; i++) {
			for (int j = 0; j < N; j++)
			{
				for (int r = 0; r < N; r++)
				{
					sum = this->multiply(this->give(i, r), sec.give(r, j));
					line = this->sum(line, sum);
				}
				newObj.insert(newObj.getInfo()+(i*this->N+j)*this->typesize, line);
			}
		}
		return newObj;
	}
	return *this;
}

class floatMatrix : public absMatrix
{
public:
	friend istream& operator>> (istream&, floatMatrix&);
	friend ostream& operator<< (ostream&, floatMatrix&);
	floatMatrix() :absMatrix() {};
	floatMatrix(int p) :absMatrix(p,sizeof(float)) {};
	~floatMatrix();
	char* give(int,int);
	char* sum(char*,char*);
	char* multiply(char*, char*);
	void insert(char*, char*);
private:

};

floatMatrix::~floatMatrix()
{
}
char * floatMatrix::give(int i, int j) // где i, j индекс включая 0(первый элемент = 0,0)
{
	char* temp = new char(sizeof(float));
	memcpy(temp,this->getInfo() + (i * this->N + j)*sizeof(float),sizeof(float));
	return temp;
}
char * floatMatrix::multiply(char *a, char *b)
{
	float* temp= new float(0);
	*temp = (float)*a * (float)*b;
	return (char*)temp;
}
char * floatMatrix::sum(char *a, char *b)
{
	float* temp= new float(0);
	*temp = (float)*a + (float)*b;
	return (char*)temp;
}
void floatMatrix::insert(char * dest, char * part)
{
	memcpy(dest, part, sizeof(float));
}
int main()
{
	setlocale(LC_ALL, "");
	floatMatrix one(2);
	floatMatrix two(2);
	cin >> one >> two;
	cout << one << two;
	(absMatrix)one = one*two;
	cout << one;
	system("pause");
}
istream & operator>>(istream &R, floatMatrix &obj)
{
	float temp;
	cout << "Введите матрицу:\n";
	for (int i = 0; i < obj.N*obj.N; i++) {
		R >> temp;
		*(obj.getInfo() + i * sizeof(float)) = (float)temp;
	}
	return R;
}

ostream & operator<<(ostream & W, floatMatrix & obj)
{
	W << "Вывод матрицы:\n";
	for (int i = 0; i < obj.N; i++) {
		for (int j = 0; j < obj.N; j++) {
			W << (float) *(obj.getInfo() + (i*obj.N + j) * sizeof(float)) << " ";
		}
		W << endl;
	}
	return W;
}



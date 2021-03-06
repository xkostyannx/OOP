#include "pch.h"
#include <iostream>
using namespace std;
class absMatrix
{
protected:
	int N; //размерность матрицы
	unsigned int typesize; //кол-ва байтов типа
public:
	virtual void float2char(float*, int) {};
	virtual float char2float(int index) { return 0; }
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
	char* info = initobj.getInfo();
	this->typesize = initobj.typesize;
	char *temp = new char[this->N*this->N*this->typesize];
	for (unsigned int i = 0; i < N*N*this->typesize; i++) {
		temp[i] = info[i];
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

absMatrix& absMatrix::operator=(absMatrix& sameobj)
{
	this->~absMatrix();
	
	this->N = sameobj.N;
	this->typesize = sameobj.typesize;
	char *temp = new char[this->N*this->N*this->typesize];
	char *info = sameobj.getInfo();
	for (unsigned int i = 0; i < N*N*this->typesize; i++) {
		temp[i] = info[i];
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
		float line = 0;	// Сумма всех произведений
		float sum = 0;	// Промежуточный результат произведения двух элементов матриц
		for (int i = 0; i < this->N; i++) {
			for (int j = 0; j < N; j++)
			{
				for (int r = 0; r < N; r++)
				{
					sum = char2float(i*this->N+r)*sec.char2float(r*this->N+j); 
					line += sum;
				}
				newObj.float2char(&line,i*this->N+j);
				line = 0;
			}
		}
		*this = newObj;
		return *this;
	}
	return *this;
}

class floatMatrix : public absMatrix
{
public:
	friend istream& operator>> (istream&, floatMatrix&);			//стандартный ввод
	friend ostream& operator<< (ostream&, floatMatrix&);			//стандартный вывод
	void float2char(float*, int);									// i элемент флоат матрицы записываем(преобразуем к char) 
	float char2float(int);
	floatMatrix() :absMatrix() {};
	floatMatrix(int p) :absMatrix(p,sizeof(float)) {};
	~floatMatrix();
	char* give(int,int);
	char* sum(char*,char*);
	char* multiply(char*, char*);
	void insert(char*, char*);
private:

};

void floatMatrix::float2char(float* value, int index)
{
	char* dest = this->getInfo();
	for (int i = 0; i < 4; i++) {
		char *temp = (dest + index * sizeof(float) + i * sizeof(char));
		char *tt = (char*)value + i * sizeof(char);
		memcpy(temp, tt, sizeof(char));
					//сначала нужный флоат + сдвиг внутри флоата
	}

}

float floatMatrix::char2float(int index)
{
	char* scr = this->getInfo() + index * sizeof(float);
	float* dest=new float;
	memcpy(dest, scr, sizeof(float));
	return *dest;
}

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
	char* temp = new char[sizeof(float)];
	*temp = (float)*a * (float)*b;
	return temp;
}
char * floatMatrix::sum(char *a, char *b)
{
	char* temp = new char[sizeof(float)];
	*temp = 0;
	*temp = (float)*a + (float)*b;
	return temp;
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
	floatMatrix three(2);
	cin >> one >> two;
	cout << one << two;
	(absMatrix) three = two*one;
	cout << three<< two;

	system("pause");
}
istream & operator>>(istream &R, floatMatrix &obj)
{
	float temp;
	cout << "Введите матрицу:\n";
	for (int i = 0; i < obj.N*obj.N; i++) {
		R >> temp;
		obj.float2char(&temp, i);
	}
	return R;
}


ostream & operator<<(ostream & W, floatMatrix & obj)
{
	W << "Вывод матрицы:\n";
	for (int i = 0; i < obj.N; i++) {
		for (int j = 0; j < obj.N; j++) {
			float temp = obj.char2float(i*obj.N+j);
			W << temp<<" ";
		}
		W << endl;
	}
	return W;
}



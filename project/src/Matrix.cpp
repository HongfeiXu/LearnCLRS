#include "Matrix.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

// Parameter Constructor 
template <typename T>
Matrix<T>::Matrix(unsigned rows_, unsigned cols_, const T& initial_)
{
	this->matData.resize(rows_);
	for (unsigned i = 0; i < rows_; i++)
	{
		this->matData[i].resize(cols_, initial_);
	}

	this->rows = rows_;
	this->cols = cols_;
}

// Copy Constructor  
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
{
	this->matData = rhs.matData;

	this->rows = rhs.getRows();
	this->cols = rhs.getCols();
}

// (Virtual) Destructor
template <typename T>
Matrix<T>::~Matrix()
{ }

// Assignment Operator  
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	this->matData = rhs.matData;

	this->rows = rhs.getRows();
	this->cols = rhs.getCols();

	return *this;
}

// Left multiplication of this matrix and another    
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix <T> &rhs) const
{
	if (this->cols != rhs.getRows())
	{
		cerr << "incompatible dimensions" << endl;
		exit(EXIT_FAILURE);
	}
	unsigned r = this->rows;
	unsigned c = rhs.getCols();

	Matrix result(r, c, 0);

	for (unsigned i = 0; i < r; i++)
	{
		for (unsigned j = 0; j < c; j++)
		{
			result(i, j) = 0;
			for (unsigned k = 0; k < this->cols; k++)
			{
				result(i, j) += this->matData[i][k] * rhs(k, j);
			}
		}
	}
	return result;
}

// Cumulative left multiplication of this matrix and another
template <typename T>
Matrix<T>& Matrix<T>::operator*= (const Matrix<T> &rhs)
{
	*this = (*this) * rhs;
	return *this;
}



// Access the individual elements
template <typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col)
{
	return this->matData[row][col];
}

// Access the individual elements (const) 
template <typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const
{
	return this->matData[row][col];
}

// Get the number of rows of the matrix 
template <typename T>
unsigned Matrix<T>::getRows() const
{
	return this->rows;
}

// Get the number of columns of the matrix 
template <typename T>
unsigned Matrix<T>::getCols() const
{
	return this->cols;
}

// Print Matrix
template <typename T>
void Matrix<T>::printMat() const
{
	for (unsigned i = 0; i < this->rows; i++)
	{
		for (unsigned j = 0; j < this->cols; j++)
		{
			cout << this->matData[i][j] << "\t";
		}
		cout << endl;
	}
}

void MatrixTest()
{
	Matrix<int> m1(1, 3, 0);
	Matrix<int> m2(3, 1, 0);

	m1(0, 0) = 1;
	m1(0, 1) = 2;
	m1(0, 2) = 3;
	m2(0, 0) = 4;
	m2(1, 0) = 5;
	m2(2, 0) = 6;

	m1.printMat();
	m2.printMat();
	
	Matrix<int> m3;
	m3 = m1 * m2;
	m3.printMat();
}

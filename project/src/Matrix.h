/***************************************************************************
*  @file       Matrix.h
*  @author     Alex.Xu
*  @mail       icevmj@gmail.com
*  @date       7.15 2017
*  @remark     a vector<vector<T>> based Matrix Class
*  @platform   visual studio 2013, windows 10
***************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using std::vector;

template <typename T>
class Matrix{
private:
	vector<vector<T>> matData;
	unsigned rows;
	unsigned cols;

public:
	Matrix() : rows(0), cols(0) { }
	Matrix(unsigned rows_, unsigned cols_, const T& initial_);
	Matrix(const Matrix<T>& rhs);
	virtual ~Matrix();

	// Operator overloading, for "standard" mathematical matrix operations 
	Matrix<T>& operator=(const Matrix<T> &rhs);
	// Matrix mathematical operations   
	Matrix<T> operator*(const Matrix <T> &rhs) const;
	Matrix<T>& operator*= (const Matrix<T> &rhs);

	// Access the individual elements                                                                                                                                                                                               
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	// Access the row and column sizes                                                                                                                                                                                              
	unsigned getRows() const;
	unsigned getCols() const;

	// Print Matrix
	void printMat() const;
};

void MatrixTest();


#endif  // !MATRIX_H

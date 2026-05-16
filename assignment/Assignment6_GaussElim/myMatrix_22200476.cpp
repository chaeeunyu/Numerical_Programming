/*----------------------------------------------------------------\
@ Numerical Programming by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 26-03-2018
Modified         : 14-10-2024
Language/ver     : C++ in MSVS2019

Description      : myMatrix.cpp
----------------------------------------------------------------*/

#include "myMatrix_22200476.h"



// Free a memory allocated matrix
void	freeMat(Matrix _A)
{
	// 1. Free allocated column memory
	for (int i = 0; i < _A.rows; i++)
		free(_A.at[i]);
	// 2. Free allocated row memory
	free(_A.at);
}

// Create a matrix from a text file
Matrix	txt2Mat(std::string _filePath, std::string _fileName)
{
	std::ifstream file;
	std::string temp_string, objFile = _filePath + _fileName + ".txt";
	int temp_int = 0, nRows = 0;

	file.open(objFile);
	if (!file.is_open()) {
		printf("\n*********************************************");
		printf("\n  Could not access file: 'txt2Mat' function");
		printf("\n*********************************************\n");
		return createMat(0, 0);
	}
	while (getline(file, temp_string, '\t'))
		temp_int++;
	file.close();

	file.open(objFile);
	while (getline(file, temp_string, '\n'))
		nRows++;
	file.close();

	int nCols = (temp_int - 1) / nRows + 1;
	Matrix Out = createMat(nRows, nCols);

	file.open(objFile);
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++) {
			file >> temp_string;
			Out.at[i][j] = stof(temp_string);
		}
	file.close();

	return Out;
}

// Create Matrix with specified size
Matrix	createMat(int _rows, int _cols)
{
	// check matrix dimension
	if (_rows < 0 || _cols < 0) {
		printf("\n****************************************************");
		printf("\n  ERROR!!: dimension error at 'createMat' function");
		printf("\n****************************************************\n");
		return createMat(0, 0);
	}

	Matrix Out;
	// 1. Allocate row array first
	Out.at = (double**)malloc(sizeof(double*) * _rows);
	// 2. Then, allocate column 
	for (int i = 0; i < _rows; i++)
		Out.at[i] = (double*)malloc(sizeof(double) * _cols);
	// 3. Initialize row & column values of a matrix
	Out.rows = _rows;
	Out.cols = _cols;

	// 4. Initialize with zero (optional)
	initMat(Out, 0);
	return Out;
}


// initialization of Matrix elements
void	initMat(Matrix _A, double _val)
{
	for (int i = 0; i < _A.rows; i++)
		for (int j = 0; j < _A.cols; j++)
			_A.at[i][j] = _val;
}

// Print matrix
void	printMat(Matrix _A, const char* _name)
{
	printf("%s =\n", _name);
	for (int i = 0; i < _A.rows; i++) {
		for (int j = 0; j < _A.cols; j++)
			printf("%15.6f\t", _A.at[i][j]);
		printf("\n");
	}
	printf("\n");
}

// Matrix addition
Matrix	addMat(Matrix _A, Matrix _B)
{
	if (_A.rows != _B.rows || _A.cols != _B.cols) {
		printf("\n*************************************************");
		printf("\n  ERROR!!: dimension error at 'addMat' function");
		printf("\n*************************************************\n");
		return createMat(0, 0);
	}

	Matrix Out = createMat(_A.rows, _B.cols);
	for (int i = 0; i < _A.rows; i++)
		for (int j = 0; j < _B.cols; j++)
			Out.at[i][j] = _A.at[i][j] + _B.at[i][j];

	return Out;
}



// Create a matrix from 1D-array
Matrix	arr2Mat(double* _1Darray, int _rows, int _cols)
{
	Matrix Output = createMat(_rows, _cols);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			Output.at[i][j] = _1Darray[i * _cols + j];

	return Output;
}


//////////////////////////////////////////////////////////////////
/*				Tutorial	&  Assignment						*/
//////////////////////////////////////////////////////////////////

// Create matrix of all zeros
extern Matrix	zeros(int _rows, int _cols)
{
	Matrix Out = createMat(_rows, _cols);
	
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			Out.at[i][j] = 0;
		}
	}

	return Out;
}


// Create matrix of all ones
extern Matrix	ones(int _rows, int _cols)
{
	Matrix Out = createMat(_rows, _cols);
	
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			Out.at[i][j] = 1;
		}
	}

	return Out;
}


// Create identity matrix
extern Matrix eye(int _rows, int _cols)
{
	Matrix Out = createMat(_rows, _cols);
	
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			if (j == i) 
				Out.at[i][j] = 1;		
			else
				Out.at[i][j] = 0;
		}
	}

	return Out;
}


// Matrix subtraction
extern	Matrix	subMat(Matrix _A, Matrix _B) {
	Matrix Out = createMat(_A.rows, _A.cols);
	
	for (int i = 0; i < _A.rows; i++) {
		for (int j = 0; j < _A.cols; j++) {
			Out.at[i][j] = _A.at[i][j] - _B.at[i][j];
		}
	}

	return Out;
}


// Multiply  matrix A and matrix B  OUT=AB
extern	Matrix	multMat(Matrix _A, Matrix _B) {
	Matrix Out = createMat(_A.rows, _B.cols);
	
	for (int k = 0; k < _A.rows; k++) {
		for (int i = 0; i < _B.cols; i++) {
			for (int j = 0; j < _B.rows; j++) {
				Out.at[k][i] += _A.at[k][j] * _B.at[j][i];
			}
		}
	}

	return Out;

}


// Multiply  matrix A with a scalar k
extern	Matrix	smultMat(Matrix _A, double _k) {
	Matrix Out = createMat(_A.rows, _A.cols);
	
	for (int i = 0; i < _A.rows; i++) {
		for (int j = 0; j < _A.cols; j++) {
			Out.at[i][j] = _A.at[i][j] * _k;
		}
	}

	return Out;
}


// Create Transpose matrix - switch the rows and columns
extern	Matrix	transpose(Matrix _A) {
	Matrix Out = createMat(_A.cols, _A.rows);
	
	for (int i = 0; i < _A.cols; i++) {
		for (int j = 0; j < _A.rows; j++) {
			Out.at[i][j] = _A.at[j][i];
		}
	}

	return Out;
}


// Copy matrix
extern	Matrix	copyMat(Matrix _A) {
	Matrix Out = createMat(_A.rows, _A.cols);
	
	for (int i = 0; i < _A.rows; i++) {
		for (int j = 0; j < _A.cols; j++) {
			Out.at[i][j] = _A.at[i][j];
		}
	}

	return Out;

}



// -------------------------------------------------
// Gauss Elimination
// -------------------------------------------------

void gaussElim(Matrix* A, Matrix* b, Matrix* U, Matrix* d)
{
	// copy matA to matU & vecb to vecd
	*U = copyMat(*A);
	*d = copyMat(*b);

	double mult = 0;
	int n = A->rows;
	//printf("n = %d\n", n);

	for (int k = 0; k < n - 1; k++) {
		for (int i = k + 1; i < n; i++) {

			mult = U->at[i][k] / U->at[k][k];
			for (int j = k; j < n; j++) {
				U->at[i][j] = U->at[i][j] - mult * U->at[k][j];  // -----> U로 불러와야 바뀐 값이 계산에 적용이 되지
			}

			d->at[i][0]= d->at[i][0] - mult * d->at[k][0]; // ********* !!!!! mult * b.at[k]
 		}
	}

	 // ---> double **at == "pointer", you cannot print it outside the function

	return;
}


// -------------------------------------------------
// Back Substitution           --- INDEX TLQKF!!!!!
// -------------------------------------------------
void backsub(Matrix* U, Matrix* d, Matrix* x)
{
	int m = U->rows;
	int n = U->cols;

	double sum = 0;

	for (int i = m - 1; i >= 0; i--) {
		sum = 0;

		for (int j = i + 1; j < n; j++) {  // n == i 일때 (맨 처음 인덱스) 문제가 생김  //e.g. for(j = 5 ; j < 5; j++) -> 걍 실행 안하고 건너뜀
	
			sum += U->at[i][j] * x->at[j][0];
		}

		x->at[i][0] = (d->at[i][0] - sum) / U->at[i][i];
	}

}


// -------------------------------------------------
// GaussElim w/ Partial Pivoting (optional)
// -------------------------------------------------
void partialPvt(Matrix* A, Matrix* b, Matrix* P)
{
	// initialization
	int m = A->rows;
	int n = A->cols;
	int big;
	double max, temp, tmpA = 0;

	// determine permutation matrix P
	for (int k = 0; k < (m - 1); k++) {

		big = k;
		max = fabs(A->at[k][k]);
		for (int i = k; i < m; i++) {
			if (fabs(A->at[i][k]) > max) {
				big = i;
				max = fabs(A->at[i][k]);
				
			}
		}
		// row swapping
		for (int j = 0; j < n; j++) {
			temp = P->at[k][j];
			tmpA = A->at[k][j];

			P->at[k][j] = P->at[big][j];
			A->at[k][j] = A->at[big][j];

			P->at[big][j] = temp;
			A->at[big][j] = tmpA;
		}
	}

	// partial pivoting
	*b = multMat(*P, *b);

}




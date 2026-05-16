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


// Multiply  matrix A and matrix B  OUT=AB  -------> 얘로 transpose 하면 결과 형태가 1x1 벡터로 나오므로 out[0][0] 이런식으로 써줘야함
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

// Multiply two vectors to make a norm (= vTv)
double vTv(Matrix v1, Matrix v2)
{
	// v1 = (1xn) vector,  v2 = (nx1) vector
	int n = v2.rows; // or n = v1.cols;
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += v1.at[0][i] * v2.at[i][0];
	}
	return sum;
}

double dotProduct(Matrix v)
{
	int n = v.rows;
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += v.at[i][0] * v.at[i][0];
	}
	sum = sqrt(sum);

	return sum;
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

}



// Forward Substitution  (Ly=b)      --- INDEX TLQKF!!!!!
void fwdsub(Matrix* L, Matrix* y, Matrix* Pb)
{
	int m = L->rows;
	int n = L->cols;
	double sum = 0;

	for (int i = 0; i < m; i++) {
		sum = 0;

		for (int j = 0; j < i; j++) {
			sum += L->at[i][j] * y->at[j][0];
		}

		y->at[i][0] = Pb->at[i][0] - sum;
	}
}



// Back Substitution  (Ux=y)         --- INDEX TLQKF!!!!!
void backsub(Matrix* U, Matrix* x, Matrix* y)
{
	int m = U->rows;
	int n = U->cols;

	double sum = 0;

	for (int i = m - 1; i >= 0; i--) {
		sum = 0;

		for (int j = i + 1; j < n; j++) {  // n == i 일때 (맨 처음 인덱스) 문제가 생김  //e.g. for(j = 5 ; j < 5; j++) -> 걍 실행 안하고 건너뜀
	
			sum += U->at[i][j] * x->at[j][0];
		}

		x->at[i][0] = (y->at[i][0] - sum) / U->at[i][i];
	}

}


// Gauss-Jordan Elimination w/ permutation
void gauss_jordanElim(Matrix* A, Matrix* b, Matrix* U, Matrix* d , Matrix* P)
{
	*U = copyMat(*A);
	*d = copyMat(*b);

	int m = U->rows;
	int n = U->cols;
	double mult = 0;
	int big;
	double max, temp, tmpU = 0;

	for (int k = 0; k < m; k++) {

		//determine permutation matrix, P
		big = k;
		max = fabs(U->at[k][k]);
		for (int i = 0; i < m; i++) {
			if (U->at[i][k] > max) {
				big = i;
				max = U->at[i][k];
			}
		}

		// row swapping
		for (int j = 0; j < n; j++) {
			temp = P->at[k][j];
			P->at[k][j] = P->at[big][j];
			P->at[big][j] = temp;

			tmpU = U->at[k][j];
			U->at[k][j] = U->at[big][j];
			U->at[big][j] = tmpU;
		}


		// gauss-jordan elimination
		for (int i = 0; i < m; i++) {
			if (i == k) {
				continue;
			}
			mult = U->at[i][k] / U->at[k][k];

			for (int j = k; j < n; j++) {
				U->at[i][j] = U->at[i][j] - mult * U->at[k][j];
			}
			d->at[i][0] = d->at[i][0] - mult * d->at[k][0];
		}
	}

	// permutation for vecd
	*d = multMat(*P, *d);
}


// gauss-jordan substitution (Ux=d)
void jordan_sub(Matrix* U, Matrix* x, Matrix* d)
{
	int m = U->rows;

	for (int i = 0; i < m; i++) {
		x->at[i][0] = d->at[i][0] / U->at[i][i];
	}
}



// Partial Pivoting (optional)
void gauss_permut(Matrix* A, Matrix* b, Matrix* U, Matrix* d, Matrix* P)
{
	// initialization
	*U = copyMat(*A);
	*d = copyMat(*b);
	int m = U->rows;
	int n = U->cols;
	double mult = 0;
	int big;
	double max, temp, tmpU = 0;
	

	// determine permutation matrix P
	for (int k = 0; k < (m - 1); k++) {

		// find the biggest fabs(element) in that column
		big = k;
		max = fabs(U->at[k][k]);
		for (int i = k; i < m; i++) {
			if (fabs(U->at[i][k]) > max) {
				big = i;
				max = fabs(U->at[i][k]);
				
			}
		}
		// row swapping (row k <-> row big)
		for (int j = 0; j < n; j++) {
			temp = P->at[k][j];
			tmpU = U->at[k][j];

			P->at[k][j] = P->at[big][j];
			U->at[k][j] = U->at[big][j];

			U->at[big][j] = tmpU;
			P->at[big][j] = temp;
		} /*END row swapping*/

		
		// gauss elimination (row reduction)
		for (int i = k + 1; i < m; i++) {

			mult = U->at[i][k] / U->at[k][k];
			for (int j = k; j < n; j++) {
				U->at[i][j] = U->at[i][j] - mult * U->at[k][j];  // -----> U로 불러와야 바뀐 값이 계산에 적용이 되지
			}

			d->at[i][0] = d->at[i][0] - mult * d->at[k][0]; // ********* !!!!! mult * b.at[k]
		}/*END row-reduction*/
		  

	}

	// partial pivoting
	*d = multMat(*P, *d);

}


// ------------------------------------
// LU decomposition w/ partial pivoting
// ------------------------------------
void LUdecomp(Matrix* A, Matrix* L, Matrix* U, Matrix* P)  // -------> divide A into L & U
{
	 // initialization
	*U = copyMat(*A);
	int m = U->rows;
	int n = U->cols;
	*L = eye(n, n);
	*P = eye(n, n);
	double mult = 0;
	int big;
	double max, temp, tmpU, tmpL = 0;



	for (int k = 0; k < (m - 1); k++) {

		//printf("k = %d\n", k);

		//partial pivoting
		// find the biggest fabs(element) in that column
		big = k;
		max = fabs(U->at[k][k]);
		for (int i = k; i < m; i++) {
			if (fabs(U->at[i][k]) > max) {
				big = i;
				max = fabs(U->at[i][k]);

			}
		}
		// row swapping (row k <-> row big)
		for (int j = 0; j < n; j++) {
			temp = P->at[k][j];
			tmpU = U->at[k][j];
			tmpL = L->at[k][j];
			
			P->at[k][j] = P->at[big][j];
			U->at[k][j] = U->at[big][j];
			L->at[k][j] = L->at[big][j];
			
			P->at[big][j] = temp;
			U->at[big][j] = tmpU;
			L->at[big][j] = tmpL;
						
		} /*END row swapping*/


		// LU decomposition (row reduction)
		for (int i = k + 1; i < m; i++) {

			mult = U->at[i][k] / U->at[k][k];
			L->at[i][k] = mult;	
			for (int j = k; j < n; j++) {
				U->at[i][j] = U->at[i][j] - mult * U->at[k][j];  // -----> U로 불러와야 바뀐 값이 계산에 적용이 되지
			}

		}/*END row-reduction*/

		/*printMat(*L, "L");
		printMat(*U, "U");
		printf("------------------\n\n");*/
	}

}



// solveLU w/ partial pivoting
void solveLU(Matrix* L, Matrix* U, Matrix* P, Matrix* b, Matrix* x)
{
	// initialize & step 1. LU factorization
	Matrix Pb = createMat(b->rows, 1);
	Matrix y = createMat(b->rows, 1);
	Pb = multMat(*P, *b);
	int m = U->rows;
	int n = U->cols;

	// step 2. Ly=b fwdsub
	double sum = 0;

	for (int i = 0; i < m; i++) {
		sum = 0;
		
		for (int j = 0; j < i; j++) {
			sum += L->at[i][j] * y.at[j][0];
		}

		y.at[i][0] = Pb.at[i][0] - sum;
	}


	// step 3. Ux=y bcksub

	for (int i = m - 1; i >= 0; i--) {
		sum = 0;

		for (int j = i + 1; j < n; j++) {  // n == i 일때 (맨 처음 인덱스) 문제가 생김  //e.g. for(j = 5 ; j < 5; j++) -> 걍 실행 안하고 건너뜀
			if (i == m - 1) {
				break;
			}
			else
			sum += U->at[i][j] * x->at[j][0];
		}

		x->at[i][0] = (y.at[i][0] - sum) / U->at[i][i];
	}

}



// inverse matrix
double invMat(Matrix* A, Matrix* Ainv)
{
	// initialize
	int m = A->rows;
	int n = A->cols;
	//Matrix A_ = copyMat(*A);
	Matrix L = zeros(m, n);
	Matrix U = zeros(m, n);
	Matrix P = eye(m, n);
	//Matrix y = zeros(n, 1);
	//Matrix v = zeros(n, 1);
	//Matrix b = zeros(n, 1);

	if (m != n) {
		printf("DIMENSION ERROR!! m != n\n\n");
		return 1;
	}

	// LUdecomp
	LUdecomp(A, &L, &U, &P); // ----------------------- done!

	// solve x
	//for (int i = 0; i < n; i++) {

	//	b.at[i][0] = 1;

	//	fwdsub(&L, &y, &b);	//------------------> 여기서 내가 solveLU를 안쓰고 바로 포워드 백섭 해버리니까
	//	backsub(&U, &v, &y);	//				b에 partial pivoting이 안되는거같음!!!

	//	for (int j = 0; j < n; j++) {
	//		Ainv->at[j][i] = v.at[j][0];
	//	}

	//	b.at[i][0] = 0;
	//}	

	Matrix e = zeros(n,1);
    Matrix x = zeros(n,1);

	for (int i = 0; i < n; i++) {
		// unit vector, e_i
		for (int j = 0; j < n; j++) {
			e.at[j][0] = 0;
		}
		e.at[i][0] = 1.0;

		// Ly = P*e, Ux = y
		solveLU(&L, &U, &P, &e, &x);

		for (int j = 0; j < n; j++) {
			Ainv->at[j][i] = x.at[j][0];
		}

	}
}



// -------------------------------------------------
// Eigenvalues / vectors
// -------------------------------------------------
	
// ---- QR decomposition ---------------------
void QRdecomp(Matrix U, Matrix* Q, Matrix* R)
{
	/* Factorization of given matrix[A] into Upper triagular[R] and orthogonormal[Q]
		 Using HouseHolder Matrix
		 Input: A(nxn)
		 Output : Q(nxn), R(nxn)*/

	// Initialization
	int n = U.rows;
	Matrix I = eye(n, n);
	Matrix H = zeros(n, n);
	*R = copyMat(U);
	*Q = I;
	Matrix c = zeros(n, 1);
	Matrix e = zeros(n, 1);
	double c_norm, v_norm = 0;


	for (int k = 0; k < n; k++) {

		// Step 1. Create vector[c]
		for (int i = 0; i < n; i++) {
			c.at[i][0] = R->at[i][k];
		}
		for (int i = 0; i < k; i++) {
			c.at[i][0] = 0;
		}
		//printMat(c, "c");

		// step 1-1. c norm - - - - -> c_norm == sqrt( |c|^2 ) == sqrt( c'c )
		Matrix cT = transpose(c);
		c_norm = sqrt(vTv(cT, c));
		

		// Step 2. Create vector[e]
		e = zeros(n, 1);
		e.at[k][0] = 1;
		if (c.at[k][0] < 0) {
			e.at[k][0] = -1;
		}
		

		// Step 3. Create vector[v]
		// (v_norm)^2 = v'v
		Matrix v = zeros(n, 1);
		v = addMat(c, smultMat(e, c_norm));

		// Step 4. Create matrix[H] 
		Matrix vT = transpose(v);
		v_norm = vTv(vT, v);
		H = subMat(I, smultMat(multMat(v, vT), (2 / v_norm)));  // H = I - 2*v*vT/vTv

		// Step 5. Update[Q], [R]
		*Q = multMat(*Q, H);
		*R = multMat(H, *R);
		/*printMat(*Q, "Q");
		printMat(*R, "R");*/

		// deallocation in the for loop
		freeMat(cT);	
		freeMat(v);		freeMat(vT);
	}

	// Deallocate Memory
	freeMat(I);		freeMat(H);		//freeMat(R);		freeMat(Q);
	freeMat(c);		freeMat(e);

}


// ---- eigenvalue ---------------------------------
Matrix eigval(Matrix A)
{
	// initialize
	int n = A.rows;
	int m = A.cols;
	if (m != n) {
		printf("Error!! A must be a square matrix!!\n");
		return A;
	}
	int itrMax = 100;
	Matrix U = copyMat(A);
	Matrix Q = eye(n, n);
	Matrix R = copyMat(A);
	Matrix lambdas = eye(n, 1);

	for (int a = 1; a <= itrMax; a++) {
		// Step 1 : A = QR decomposition
		QRdecomp(U, &Q, &R);
		/*printMat(Q, "Q");
		printMat(R, "R");*/
		
		// Step 2: Create Similar Matrix A = Q'AQ
		U = multMat(R, Q);
		/*if (a % 10 == 0) {
			printf("iteration %d \n", a);
			printMat(U, "U");
		}	*/			
	}

	// Step 3: eigenvalues from U
	for (int b = 0; b < n; b++) {
		lambdas.at[b][0] = U.at[b][b];
	}


	// deallocation
	freeMat(U);		freeMat(Q);		freeMat(R);


	return lambdas;
}




// ---- eigenvectors --------------------------------
Matrix eigvec(Matrix A)	
{
	int n = A.rows;
	
	Matrix lambdas = eigval(A);	
	Matrix v_final = zeros(n, n);
	

	for (int k = 0; k < n; k++) {	// k -> v=1,2,3
		printf("-----------\n");
		printf("k = %d\n", k);
		Matrix B = copyMat(A);
		// step 1. create matrix B = A - lambda*I
		for (int i = 0; i < n; i++) {
			B.at[i][i] -= lambdas.at[k][0]; 
		}
		printMat(B, "B");
		Matrix b = zeros(n - 1, n - 1);
		Matrix b_inv = zeros(n - 1, n - 1);
		Matrix vecb = zeros(n - 1, 1);
		Matrix tmpv = zeros(n - 1, 1);
		Matrix v3 = zeros(n, 1);

		// step 2. create (n-1)x(n-1) matrix b 
		int row_ = 0, col = 0;
		for (int i = 0; i < n; i++) {
			if (i == k) {
				continue;
			}
			

			for (int j = 0; j < n; j++) {
				if (j == k) {
					continue;
				}
				b.at[row_][col] = B.at[i][j];
				col++;
			}
			row_++;
			col = 0;
		}
		row_ = 0;
		printMat(b, "b1"); 

		// step 3. get a matrix 'b_inv' & a vector 'vecb'
		invMat(&b, &b_inv);		
		printMat(b_inv, "binv");
 
		for (int a = 0; a < n; a++) {
			if (a == k)
				continue;
			vecb.at[row_][0] = -B.at[a][k];
			row_++;
		}
		printMat(vecb, "vecb"); 
		
		// step 4. get the vectors v123 by multMat(b_inv, b_minus)
		tmpv = multMat(b_inv, vecb);
		printMat(tmpv, "v2");

		int idx = 0;
		for (int y = 0; y < n; y++) {
			if (y == k)
				v3.at[y][0] = 1.0;
			else
				v3.at[y][0] = tmpv.at[idx++][0];
			
		}
		printMat(v3, "v3");

		

		// step 5. normalizing
		Matrix vT = transpose(v3);
		double vnorm = sqrt(vTv(vT, v3));  

		v3 = smultMat(v3, 1.0 / vnorm);

		// step 6. get the eigenvector by gathering v123
		for (int c = 0; c < n; c++) {
			v_final.at[c][k] = v3.at[c][0];
		}


		// Deallocation in for loop 
		freeMat(B);			freeMat(b);			freeMat(b_inv);
		freeMat(vecb);		freeMat(tmpv);		freeMat(v3); 
		freeMat(vT);
	
	} // end k
	

	freeMat(lambdas);


	return v_final;
}




// --- eigenvalues/vectors (V/D) -------------------------
double eig(Matrix A, Matrix* V, Matrix* D)
{
	int n = A.rows;
	int m = A.cols;
	if (n != m) {
		printf("Dimension ERROR!!!\n\n");
		return 1;
	}

	*V = eigvec(A);
	Matrix lambdas = eigval(A);

	// sorting in a descending order
	double tmp = 0;
	Matrix tmpv = createMat(n, 1);
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (lambdas.at[i][0] < lambdas.at[j][0]) {  
				tmp = lambdas.at[i][0];
				for (int r = 0; r < n; r++) {
					tmpv.at[r][0] = V->at[r][i];
				}
				
				lambdas.at[i][0] = lambdas.at[j][0];
				for (int r = 0; r < n; r++) {
					V->at[r][i] = V->at[r][j];
				}
				lambdas.at[j][0] = tmp;
				for (int r = 0; r < n; r++) {
					V->at[r][j] = tmpv.at[r][0];
				}
			}
		} // end j
	} // end i
	
	*D = zeros(n, n);
	for (int z = 0; z < n; z++) {
		D->at[z][z] = lambdas.at[z][0];
	}

	// Deallocation memory
	freeMat(lambdas);		freeMat(tmpv);

}



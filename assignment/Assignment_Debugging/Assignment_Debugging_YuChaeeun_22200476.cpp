#include <stdio.h>
#include "../../include/NP_debugging_header.h"

/////////////////////////////////////////////////////////
//	Function Declaration
/////////////////////////////////////////////////////////

int sum_int(int a, int b);

/////////////////////////////////////////////////////////
//	MAIN Function
/////////////////////////////////////////////////////////

int main() {
	int a = 1;
	int b = 2;
	int c = 3;
	int	d = 4;

	int count = 0;

	for (int j = 0; j < 6; j++) {
		if (j == 5)
			printf("j is %d\n", j);
	}

	printf("a= %d,  b= %d \n", a, b);
	printf("sum is %d\n", sum_int(a, b));
	printf("difference is %d\n", subtract_int(a, b));

	return 0;
}


	/////////////////////////////////////////////////////////
	//					Function Definition
	/////////////////////////////////////////////////////////

	// Sum of two integers
	int sum_int(int a, int b) {
		int sum = a + b;
		return sum;
	}
